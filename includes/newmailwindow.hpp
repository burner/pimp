#ifndef NEWMAILWINDOW
#define NEWMAILWINDOW

#include <QMainWindow>
#include <ui_newmailwindow.h>

class Ui_Dialog;

class NewMailWindow : public QMainWindow {
	Q_OBJECT
	public:
		NewMailWindow(QWidget* parent = NULL);

	private:
		Ui::NewMailWindow ui;
		void execCommand(const QString&);
		void execCommand(const QString&, const QString &);
		bool queryCommandState(const QString&);
		QDialog *insertHtmlDialog;
		Ui_Dialog *ui_dialog;

	private slots:
		void sendButtonClick();
		void closeCheck();
		void zoomOut();
		void zoomIn();
		void changeZoom(int);
		void styleParagraph();
		void styleHeading1();
		void styleHeading2();
		void styleHeading3();
		void styleHeading4();
		void styleHeading5();
		void styleHeading6();
		void stylePreformatted();
		void styleAddress();
		void formatStrikeThrough();
		void formatAlignLeft();
		void formatAlignCenter();
		void formatAlignRight();
		void formatAlignJustify();
		void formatIncreaseIndent();
		void formatDecreaseIndent();
		void formatNumberedList();
		void formatBulletedList();
		void formatFontName();
		void formatFontSize();
		void formatTextColor();
		void formatBackgroundColor();
		void insertImage();
		void createLink();
		void insertHtml();
};
#endif
