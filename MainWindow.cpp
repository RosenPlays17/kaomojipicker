#include <QClipboard>
#include <QDir>
#include <QGuiApplication>
#include <QStandardPaths>
#include "MainWindow.h"

static QString capitalizeFirst(QString text) {
    if (!text.isEmpty()) {
        text[0] = text[0].toUpper();
    }
    return text;
}

MainWindow::MainWindow() {
    mainLayout = new QGridLayout;
    kaomojiCategories = new QListWidget;
    kaomojiListStack = new QStackedWidget;

    kaomojiCategories->setFixedWidth(0);
    mainLayout->addWidget(kaomojiCategories, 0, 0);
    mainLayout->addWidget(kaomojiListStack, 0, 1);

    QStringList dataDirs = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);

    bool dirFound = false;
    foreach (QString directory, dataDirs) {
        directory += "/kaomojipicker/kaomoji";
        if (QFile::exists(directory)) {
            dirFound = true;
            QDir dir(directory);
            foreach (const QFileInfo &fileInfo, dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
                addCategory(fileInfo);
            }
        }
    }
    if (!dirFound) {
        qFatal("Could not find kaomoji data.");
    }

    connect(kaomojiCategories, &QListWidget::itemClicked, this, &MainWindow::categoryClicked);

    mainLayout->setColumnStretch(0, 0);
    mainLayout->setColumnStretch(1, 1);
    setLayout(mainLayout);
    show();
}

void MainWindow::copyToClipboard(QListWidgetItem* item) {
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(item->text());
}

void MainWindow::categoryClicked(QListWidgetItem* item) {
    kaomojiListStack->setCurrentWidget(kaomojiLists[item->text()]);
}

void MainWindow::addCategory(const QFileInfo &fileInfo) {
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

    connect(listView, &QListWidget::itemClicked, this, &MainWindow::copyToClipboard);

    QString categoryName = capitalizeFirst(fileInfo.completeBaseName());
    kaomojiLists[categoryName] = listView;
    kaomojiListStack->addWidget(listView);
    kaomojiCategories->addItem(categoryName);
    kaomojiCategories->setFixedWidth(std::max(kaomojiCategories->width(), metrics.horizontalAdvance(categoryName) + 24));
}
