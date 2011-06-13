/*
 * Copyright (C) 2011 Sebastien Helleu <flashcode@flashtux.org>
 *
 * This file is part of WeeChat, the extensible chat client.
 *
 * WeeChat is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WeeChat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WeeChat.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __WEECHAT_HDATA_H
#define __WEECHAT_HDATA_H 1

#define HDATA_VAR(__struct, __name, __type)                             \
    hdata_new_var (hdata, #__name, offsetof (__struct, __name),         \
                   WEECHAT_HDATA_##__type);
#define HDATA_LIST(__name) hdata_new_list (hdata, #__name, &(__name));

struct t_hdata
{
    char *name;                        /* name of hdata                     */
    struct t_hashtable *hash_var;      /* hashtable with offset of vars     */
    char *var_prev;                    /* name of var with pointer to       */
                                       /* previous element in list          */
    char *var_next;                    /* name of var with pointer to       */
                                       /* next element in list              */
    struct t_hashtable *hash_list;     /* hashtable with pointers on lists  */
                                       /* (used to search objects)          */
    struct t_hdata *prev_hdata;        /* link to previous hdata            */
    struct t_hdata *next_hdata;        /* link to next hdata                */
};

extern struct t_hdata *weechat_hdata;
extern struct t_hdata *last_weechat_hdata;

extern char *hdata_type_string[];

extern struct t_hdata *hdata_new (const char *hdata_name, const char *var_prev,
                                  const char *var_next);
extern void hdata_new_var (struct t_hdata *hdata, const char *name, int offset,
                           int type);
extern void hdata_new_list (struct t_hdata *hdata, const char *name,
                            void *pointer);
extern int hdata_get_var_offset (struct t_hdata *hdata, const char *name);
extern int hdata_get_var_type (struct t_hdata *hdata, const char *name);
extern const char *hdata_get_var_type_string (struct t_hdata *hdata,
                                              const char *name);
extern void *hdata_get_var (struct t_hdata *hdata, void *pointer,
                            const char *name);
extern void *hdata_get_var_at_offset (struct t_hdata *hdata, void *pointer,
                                      int offset);
extern void *hdata_get_list (struct t_hdata *hdata, const char *name);
extern void *hdata_move (struct t_hdata *hdata, void *pointer, int count);
extern int hdata_integer (struct t_hdata *hdata, void *pointer,
                          const char *name);
extern long hdata_long (struct t_hdata *hdata, void *pointer,
                        const char *name);
extern const char *hdata_string (struct t_hdata *hdata, void *pointer,
                                 const char *name);
extern void *hdata_pointer (struct t_hdata *hdata, void *pointer,
                            const char *name);
extern time_t hdata_time (struct t_hdata *hdata, void *pointer,
                          const char *name);
extern const char *hdata_get_string (struct t_hdata *hdata,
                                     const char *property);
extern void hdata_print_log ();

#endif /* __WEECHAT_HDATA_H */