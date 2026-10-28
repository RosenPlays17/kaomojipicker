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
    QGridLayout* mainLayout;
    QListWidget* kaomojiCategories;
    QStackedWidget* kaomojiListStack;
    QMap<QString,QListWidget*> kaomojiLists;

public:
    MainWindow();

private slots:
    void copyToClipboard(QListWidgetItem *item);
    void categoryClicked(QListWidgetItem *item);

private:
    void addCategory(const QFileInfo &fileInfo);
};

#endif //KAOMOJI_MAINWINDOW_H
