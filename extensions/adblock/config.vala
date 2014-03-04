/*
 Copyright (C) 2014 Christian Dywan <christian@twotoasts.de>

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 See the file COPYING for the full license text.
*/

namespace Adblock {
    public class Config : GLib.Object {
        List<Subscription> subscriptions;
        string? path;
        public KeyFile keyfile;
        bool should_save;

        public Config (string? path, string? presets) {
            should_save = false;
            subscriptions = new GLib.List<Subscription> ();
            this.path = path;
            load_file (path);
            load_file (presets);

            size = subscriptions.length ();
            should_save = true;
        }

        void load_file (string? filename) {
            if (filename == null)
                return;

            keyfile = new GLib.KeyFile ();
            try {
                keyfile.load_from_file (filename, GLib.KeyFileFlags.NONE);
                string[] filters = keyfile.get_string_list ("settings", "filters");
                foreach (string filter in filters) {
                    bool active = false;
                    string uri = filter;
                    if (filter.has_prefix ("http-"))
                        uri = "http:" + filter.substring (6);
                    else if (filter.has_prefix ("file-"))
                        uri = "file:" + filter.substring (6);
                    else if (filter.has_prefix ("https-"))
                        uri = "https:" + filter.substring (7);
                    else
                        active = true;
                    Subscription sub = new Subscription (uri);
                    sub.active = active;
                    sub.add_feature (new Updater ());
                    add (sub);
                }
            } catch (KeyFileError.KEY_NOT_FOUND key_error) {
                /* It's no error if a key is missing */
            } catch (KeyFileError.GROUP_NOT_FOUND group_error) {
                /* It's no error if a group is missing */
            } catch (FileError.NOENT exist_error) {
                /* It's no error if no config file exists */
            } catch (GLib.Error settings_error) {
                warning ("Error reading settings from %s: %s\n", filename, settings_error.message);
            }
        }

        void active_changed (Object subscription, ParamSpec pspec) {
            update_filters ();
        }

        void update_filters () {
            var filters = new StringBuilder ();
            foreach (var sub in subscriptions) {
                if (!sub.mutable)
                    continue;
                if (sub.uri.has_prefix ("http:") && !sub.active)
                    filters.append ("http-" + sub.uri.substring (4));
                else if (sub.uri.has_prefix ("file:") && !sub.active)
                    filters.append ("file-" + sub.uri.substring (4));
                else if (sub.uri.has_prefix ("https:") && !sub.active)
                    filters.append ("https-" + sub.uri.substring (5));
                else
                    filters.append (sub.uri);
                filters.append_c (';');
            }

            if (filters.str.has_suffix (";"))
                filters.truncate (filters.len - 1);
            string[] list = filters.str.split (";");
            keyfile.set_string_list ("settings", "filters", list);

            save ();
        }


        public void save () {
            try {
                FileUtils.set_contents (path, keyfile.to_data ());
            } catch (Error error) {
                warning ("Failed to save settings: %s", error.message);
            }
        }

        /* foreach support */
        public new Subscription? get (uint index) {
            return subscriptions.nth_data (index);
        }
        public uint size { get; private set; }

        bool contains (Subscription subscription) {
            foreach (var sub in subscriptions)
                if (sub.uri == subscription.uri)
                    return true;
            return false;
        }

        public bool add (Subscription sub) {
            if (contains (sub))
                return false;

            sub.notify["active"].connect (active_changed);
            subscriptions.append (sub);
            size++;
            if (should_save)
                update_filters ();
            return true;
        }

        public void remove (Subscription sub) {
            if (!contains (sub))
                return;

            subscriptions.remove (sub);
            sub.notify["active"].disconnect (active_changed);
            update_filters ();
            size--;
        }
    }
}
