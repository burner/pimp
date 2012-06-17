#ifndef RSSMAINWIDGET
#define RSSMAINWIDGET

#include <QWidget>
#include <QtSql>
#include <ui_rssmainwidget.h>

class RssMainWidget : public QWidget {
	Q_OBJECT
	public:
		RssMainWidget(QWidget* parent = NULL);
		void init();

	private:
		Ui::RssMainWidget ui;
		QSqlDatabase db;
		QSqlTableModel *feedModel;
		QSqlTableModel *feedEntryModel;
		bool initDB(QSqlDatabase&);
		bool addFeed(QSqlQuery&, const QString&, const QString&);
		void getFeed(const QString&, const int);

	private slots:
		void newFeed();
		void onRemoveClick();
		void getFeeds();
		void selectFeedEntryChanged(QModelIndex, QModelIndex);
		void selectFeedEntriesChanged(QModelIndex oldFeed, QModelIndex newFeed);

	public slots:
		void insertNewFeed(const QString, const QString);

};
#endif
