// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "messagebox.h"

#include "defs.h"


MessageBox::MessageBox(QMessageBox::Icon new_icon, QMessageBox::StandardButtons new_buttons) :
    icon{new_icon},
    buttons{new_buttons}
{
    // ...
}


void MessageBox::setParent(QWidget* new_parent)
{
    parent = new_parent;
}


void MessageBox::setTitle(const QString& new_title)
{
    title = new_title;
}


void MessageBox::setText(const QString& new_text)
{
    text = new_text;
}


int MessageBox::run()
{
    QMessageBox message_box(parent);
    message_box.setText(text);
    message_box.setWindowTitle(title);
    message_box.setIcon(icon);
    message_box.setStandardButtons(buttons);

    if (text.count() > Constants::messageboxContentMaxSize())
    {
        message_box.setDetailedText(text);
        message_box.setText(text.left(Constants::messageboxContentMaxSize()).append(" ... "));
    }

    return message_box.exec();
}
