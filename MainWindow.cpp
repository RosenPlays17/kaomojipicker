#include "MainWindow.h"
#include <QDir>
#include <QStandardPaths>
#include <QClipboard>
#include <QGuiApplication>

static QString capitalizeFirst(QString text) {
    if (!text.isEmpty()) {
        text[0] = text[0].toUpper();
    }
    return text;
}

MainWindow::MainWindow() {
    kaomojiTabWidget = new QTabWidget;

    QStringList dataDirs = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    QStringList files;

    bool dirFound = false;
    foreach (QString directory, dataDirs) {
        directory += "/kaomojipicker/kaomoji";
        if (QFile::exists(directory)) {
            dirFound = true;
            QDir dir(directory);
            foreach (const QFileInfo &fileInfo, dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
                addTab(fileInfo);
            }
        }
    }
    if (!dirFound) {
        qFatal("Could not find kaomoji data.");
    }

    kaomojiTabWidget->setTabPosition(QTabWidget::West);
    kaomojiTabWidget->show();
}

void MainWindow::copyToClipboard(QListWidgetItem *item) {
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(item->text());
}

void MainWindow::addTab(const QFileInfo &fileInfo) {
    QListWidget* listView = new QListWidget;
    const QFontMetrics metrics(listView->font());
    int width = 0;

    QFile file(fileInfo.absoluteFilePath());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(&file);
        while (!ts.atEnd()) {
            QString line = ts.readLine();
            width = std::max(width, metrics.horizontalAdvance(line));
            listView->addItem(line);
        }
    }
    file.close();

    listView->setGridSize(QSize(width + 12, metrics.height() + 12));
    listView->setViewMode(QListWidget::IconMode);
    listView->setFlow(QListWidget::Flow::LeftToRight);
    listView->setWrapping(true);
    listView->setResizeMode(QListWidget::ResizeMode::Adjust);

    connect(listView, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(copyToClipboard(QListWidgetItem*)));

    kaomojiTabWidget->addTab(listView, capitalizeFirst(fileInfo.completeBaseName()));
}
