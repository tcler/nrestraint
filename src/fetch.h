/*
    This file is part of Restraint.

    Restraint is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Restraint is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Restraint.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _RESTRAINT_FETCH_H
#define _RESTRAINT_FETCH_H

#include "utils.h"

#include <stdint.h>
#include <glib.h>
#include <gio/gio.h>
#include <libsoup/soup.h>
#include <curl/curl.h>

#define LARGE_PACKET_MAX 65520

typedef void (*FetchFinishCallback) (GError *error,
                                     guint32 match_cnt,
                                     guint32 nonmatch_cnt,
                                     gpointer user_data);

typedef void (*ArchiveEntryCallback) (const gchar *entry,
                                      gpointer user_data);

typedef struct {
    gchar buf[LARGE_PACKET_MAX];
    SoupURI *url;
    const gchar *base_path;
    GSocketConnection *connection;
    GSocketClient *client;
    GInputStream *istream;
    GOutputStream *ostream;
    struct archive *a;
    struct archive *ext;
    FetchFinishCallback finish_callback;
    ArchiveEntryCallback archive_entry_callback;
    gpointer user_data;
    GError *error;
    guint32 match_cnt;
    guint32 nonmatch_cnt;
    gboolean keepchanges;
    gboolean ssl_verify;
    gpointer private_data;
    gchar curl_error_buf[CURL_ERROR_SIZE];
} FetchData;

#define RESTRAINT_FETCH_ERROR restraint_fetch_error ()
GQuark restraint_fetch_error (void);

typedef enum {
    RESTRAINT_FETCH_GIT_HUP_ERROR,
    RESTRAINT_FETCH_GIT_PROTOCOL_ERROR,
    RESTRAINT_FETCH_GIT_NAK_ERROR,
    RESTRAINT_FETCH_GIT_REMOTE_ERROR,
} RestraintFetchError;

#define RESTRAINT_FETCH_LIBARCHIVE_ERROR restraint_fetch_libarchive_error()
GQuark restraint_fetch_libarchive_error(void);

#endif
