/*
 * Copyright (C) 2020 PandaOS Team.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QDirIterator>
#include <QTranslator>
#define TRANSALTIONPATH "/usr/share/panda-dock/translations"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir dir(TRANSALTIONPATH);
    if (dir.exists()) {
        QDirIterator qmIt(TRANSALTIONPATH, QStringList() << QString("*%1.qm").arg(QLocale::system().name()), QDir::Files);
        while (qmIt.hasNext()) {
            qmIt.next();
            QFileInfo finfo = qmIt.fileInfo();
            QTranslator *translator = new QTranslator;
            if (translator->load(finfo.baseName(), finfo.absolutePath())) {
                qApp->installTranslator(translator);
            }
        }
    }
    a.setApplicationName("panda-dock");
    a.setApplicationDisplayName("PandaOS");

    MainWindow w;
    w.show();

    return a.exec();
}
