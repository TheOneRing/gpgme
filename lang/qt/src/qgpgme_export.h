/*  qgpgme_export.h - Export macros for qgpgme

    This file is part of qgpgme, the Qt API binding for gpgme
    Copyright (c) 2016 by Bundesamt für Sicherheit in der Informationstechnik
    Software engineering by Intevation GmbH

    QGpgME is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    QGpgME is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    In addition, as a special exception, the copyright holders give
    permission to link the code of this program with any edition of
    the Qt library by Trolltech AS, Norway (or with modified versions
    of Qt that use the same license as Qt), and distribute linked
    combinations including the two.  You must obey the GNU General
    Public License in all respects for all of the code used other than
    Qt.  If you modify this file, you may extend this exception to
    your version of the file, but you are not obligated to do so.  If
    you do not wish to do so, delete this exception statement from
    your version.
*/

#ifndef QGPGME_EXPORT_H
#define QGPGME_EXPORT_H

#ifdef QGPGME_STATIC_DEFINE
#  define QGPGME_EXPORT
#  define QGPGME_NO_EXPORT
#else
#  ifndef QGPGME_EXPORT
#    ifdef BUILDING_QGPGME
        /* We are building this library */
#      ifdef WIN32
#       define QGPGME_EXPORT __declspec(dllexport)
#      else
#       define QGPGME_EXPORT __attribute__((visibility("default")))
#      endif
#    else
        /* We are using this library */
#      ifdef WIN32
#       define QGPGME_EXPORT __declspec(dllimport)
#      else
#       define QGPGME_EXPORT __attribute__((visibility("default")))
#      endif
#    endif
#  endif

#  ifndef QGPGME_NO_EXPORT
#    ifdef WIN32
#     define QGPGME_NO_EXPORT
#    else
#     define QGPGME_NO_EXPORT __attribute__((visibility("hidden")))
#    endif
#  endif
#endif

#ifndef QGPGME_DEPRECATED
#  if WIN32
#    define QGPGME_DEPRECATED __declspec(deprecated)
#  else
#    define QGPGME_DEPRECATED __attribute__ ((__deprecated__))
#  endif
#endif

#ifndef QGPGME_DEPRECATED_EXPORT
#  define QGPGME_DEPRECATED_EXPORT QGPGME_EXPORT QGPGME_DEPRECATED
#endif

#ifndef QGPGME_DEPRECATED_NO_EXPORT
#  define QGPGME_DEPRECATED_NO_EXPORT QGPGME_NO_EXPORT QGPGME_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define QGPGME_NO_DEPRECATED
#endif

#endif
