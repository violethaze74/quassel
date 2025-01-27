/***************************************************************************
 *   Copyright (C) 2005-2021 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "ldapescaper.h"

QString LdapEscaper::escapeQuery(const QString& filter)
{
    QString result;
    for (const auto character : filter) {
        if (character > 0x7F ||
            character == '*' ||
            character == '(' ||
            character == ')' ||
            character == '\\' ||
            character == '\0') {
            for (uint8_t byte: QString(character).toUtf8()) {
                result += "\\";
                result += QString::number(byte, 16).rightJustified(2, '0');
            }
        } else {
            result += character;
        }
    }
    return result;
}
