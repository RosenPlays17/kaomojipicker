#ifndef KAOMOJI_MAINWINDOW_H
#define KAOMOJI_MAINWINDOW_H

#include <QListWidget>
#include <QFileInfo>
#include <QWidget>

class MainWindow : QWidget {
    Q_OBJECT

private:
    QTabWidget* kaomojiTabWidget;

public:
    MainWindow();

private slots:
    void copyToClipboard(QListWidgetItem *item);

private:
    void addTab(const QFileInfo &fileInfo);
};

#endif //KAOMOJI_MAINWINDOW_H
