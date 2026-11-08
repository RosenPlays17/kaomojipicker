#ifndef KAOMOJI_MAINWINDOW_H
#define KAOMOJI_MAINWINDOW_H

#include <QFileInfo>
#include <QGridLayout>
#include <QListWidget>
#include <QMap>
#include <QStackedWidget>
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

private:
    QGridLayout mainLayout;
    QListWidget kaomojiCategories;
    QStackedWidget kaomojiListStack;
    QMap<QString,QListWidget*> kaomojiLists;

public:
    MainWindow();

private slots:
    static void copyToClipboard(const QListWidgetItem* item);
    void categoryClicked(const QListWidgetItem* item);

private:
    void searchDataDirs();
    void addCategory(const QFileInfo& fileInfo);
};

#endif //KAOMOJI_MAINWINDOW_H
