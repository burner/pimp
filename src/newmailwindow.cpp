#include <QtGui>
#include <QtWebKit>

#include <vmime/vmime.hpp>

#include "ui_inserthtmldialog.h"

#include <newmailwindow.hpp>
#include <debug.hpp>
#include <highlighter.hpp>

#define FOLLOW_ENABLE(a1, a2) a1->setEnabled(ui.webView->pageAction(a2)->isEnabled())
#define FOLLOW_CHECK(a1, a2) a1->setChecked(ui.webView->pageAction(a2)->isChecked())

#define FORWARD_ACTION(action1, action2) \
    connect(action1, SIGNAL(clicked()), \
            ui.webView->pageAction(action2), SLOT(trigger())); \
    connect(ui.webView->pageAction(action2), \
            SIGNAL(changed()), SLOT(adjustActions()));

NewMailWindow::NewMailWindow(QWidget* parent) : QMainWindow(parent),
		insertHtmlDialog(NULL), ui_dialog(0) {
	ui.setupUi(this);
	ui.webView->page()->setContentEditable(true);

	// init the zoom slider correctly
	ui.zoomSlider->setMaximumWidth(150);
	ui.zoomSlider->setRange(25, 400);
	ui.zoomSlider->setSingleStep(25);
	ui.zoomSlider->setPageStep(100);
	ui.zoomSlider->setValue(100);

    connect(ui.tabWidget, SIGNAL(currentChanged(int)), this,
		SLOT(changeTab(int)));

    highlighter = new Highlighter(ui.plainTextView->document());

    FORWARD_ACTION(ui.undoButton, QWebPage::Undo);
    FORWARD_ACTION(ui.redoButton, QWebPage::Redo);
    FORWARD_ACTION(ui.cutButton, QWebPage::Cut);
    FORWARD_ACTION(ui.copyButton, QWebPage::Copy);
    FORWARD_ACTION(ui.pasteButton, QWebPage::Paste);
    FORWARD_ACTION(ui.boldButton, QWebPage::ToggleBold);
    FORWARD_ACTION(ui.italicButton, QWebPage::ToggleItalic);
    FORWARD_ACTION(ui.underlineButton, QWebPage::ToggleUnderline);

	QObject::connect(ui.sendButton, SIGNAL(clicked()), this, 
		SLOT(sendButtonClick()));
	QObject::connect(ui.action_Quit, SIGNAL(triggered()), this, 
		SLOT(closeCheck()));
	QObject::connect(ui.zoomOutButton, SIGNAL(clicked()), this,
		SLOT(zoomOut()));
	QObject::connect(ui.zoomInButton, SIGNAL(clicked()), this,
		SLOT(zoomIn()));
	QObject::connect(ui.zoomSlider, SIGNAL(valueChanged(int)), 
		SLOT(changeZoom(int)));

    QObject::connect(ui.addImageButton, SIGNAL(clicked()), 
		this, SLOT(insertImage()));
    QObject::connect(ui.insertUrlButton, SIGNAL(clicked()), 
		this, SLOT(createLink()));
    QObject::connect(ui.insertHtmlButton, SIGNAL(clicked()), this,
		SLOT(insertHtml()));

    QObject::connect(ui.actionAdd_Paragraph, SIGNAL(triggered()), this,
		SLOT(styleParagraph()));
    QObject::connect(ui.actionAdd_Heading_1, SIGNAL(triggered()), this,
		SLOT(styleHeading1()));
    QObject::connect(ui.actionAdd_Heading_2, SIGNAL(triggered()), this,
		SLOT(styleHeading2()));
    QObject::connect(ui.actionAdd_Heading_3, SIGNAL(triggered()), this,
		SLOT(styleHeading3()));
    QObject::connect(ui.actionAdd_Heading_4, SIGNAL(triggered()), this,
		SLOT(styleHeading4()));
    QObject::connect(ui.actionAdd_Heading_5, SIGNAL(triggered()), this,
		SLOT(styleHeading5()));
    QObject::connect(ui.actionAdd_Heading_6, SIGNAL(triggered()), this,
		SLOT(styleHeading6()));

    QObject::connect(ui.webView->page(), SIGNAL(selectionChanged()), this, 
		SLOT(adjustActions()));
    QObject::connect(ui.webView->page(), SIGNAL(contentsChanged()), this,
		SLOT(adjustSource()));

    QObject::connect(ui.strikethroughButton, SIGNAL(clicked()), this,
		SLOT(formatStrikeThrough()));
    QObject::connect(ui.leftAlignButton, SIGNAL(clicked()), this,
		SLOT(formatAlignLeft()));
    QObject::connect(ui.centeredButton, SIGNAL(clicked()), this,
		SLOT(formatAlignCenter()));
    QObject::connect(ui.rightAlignButton, SIGNAL(clicked()), this,
		SLOT(formatAlignRight()));
    QObject::connect(ui.fillButton, SIGNAL(clicked()), this,
		SLOT(formatAlignJustify()));
    QObject::connect(ui.decreaseIndentButton, SIGNAL(clicked()), this,
		SLOT(formatDecreaseIndent()));
    QObject::connect(ui.increaseIndentButton, SIGNAL(clicked()), this,
		SLOT(formatIncreaseIndent()));
    QObject::connect(ui.numberedButton, SIGNAL(clicked()), this,
		SLOT(formatNumberedList()));
    QObject::connect(ui.bulletButton, SIGNAL(clicked()), this,
		SLOT(formatBulletedList()));
}


void NewMailWindow::sendButtonClick() {
	debug()<<"Here";
	LOG("%s", "here also");
}

void NewMailWindow::closeCheck() {
	LOG("here");
	close();
}

void NewMailWindow::zoomOut() {
	int percent = static_cast<int>(ui.webView->zoomFactor() * 100);
	if(percent > 25) {
		percent -= 25;
		percent = 25 * (int((percent + 25 - 1) / 25));
		qreal factor = static_cast<qreal>(percent) / 100;
		LOG("zoom factor %f", static_cast<double>(factor));
		ui.webView->setZoomFactor(factor);
		ui.zoomOutButton->setEnabled(percent > 25);
		ui.zoomInButton->setEnabled(true);
		ui.zoomSlider->setValue(percent);
	}
}

void NewMailWindow::zoomIn() {
	int percent = static_cast<int>(ui.webView->zoomFactor() * 100);
	if(percent < 400) {
		percent += 25;
		percent = 25 * (int(percent / 25));
		qreal factor = static_cast<qreal>(percent) / 100;
		LOG("zoom factor %f", static_cast<double>(factor));
		ui.webView->setZoomFactor(factor);
		ui.zoomInButton->setEnabled(percent < 400);
		ui.zoomOutButton->setEnabled(true);
		ui.zoomSlider->setValue(percent);
	}
}

void NewMailWindow::changeZoom(int percent) {
	ui.zoomOutButton->setEnabled(percent > 25);
	ui.zoomInButton->setEnabled(percent < 400);
	qreal factor = static_cast<qreal>(percent) / 100;
	LOG("zoom factor %f", static_cast<double>(factor));
	ui.webView->setZoomFactor(factor);

	ui.zoomSlider->setValue(percent);
}

void NewMailWindow::execCommand(const QString &cmd) {
	QWebFrame *frame = ui.webView->page()->mainFrame();
	LOG("%s", cmd.toStdString());
	QString js = QString("document.execCommand(\"%1\", false, null)").arg(cmd);
	frame->evaluateJavaScript(js);
}

void NewMailWindow::execCommand(const QString &cmd, const QString &arg) {
	QWebFrame *frame = ui.webView->page()->mainFrame();
	LOG("%s %s", cmd.toStdString(), arg.toStdString());
	QString js = QString("document.execCommand(\"%1\", false, \"%2\")").
		arg(cmd).arg(arg);
	frame->evaluateJavaScript(js);
}

bool NewMailWindow::queryCommandState(const QString &cmd) {
	QWebFrame *frame = ui.webView->page()->mainFrame();
	QString js = QString("document.queryCommandState(\"%1\", false, null)").
		arg(cmd);
	QVariant result = frame->evaluateJavaScript(js);
	return result.toString().simplified().toLower() == "true";
}

void NewMailWindow::styleParagraph() {
	execCommand("formatBlock", "p");
}

void NewMailWindow::styleHeading1() {
	execCommand("formatBlock", "h1");
}

void NewMailWindow::styleHeading2() {
	execCommand("formatBlock", "h2");
}

void NewMailWindow::styleHeading3() {
	execCommand("formatBlock", "h3");
}

void NewMailWindow::styleHeading4() {
	execCommand("formatBlock", "h4");
}

void NewMailWindow::styleHeading5() {
	execCommand("formatBlock", "h5");
}

void NewMailWindow::styleHeading6() {
	execCommand("formatBlock", "h6");
}

void NewMailWindow::stylePreformatted() {
	execCommand("formatBlock", "pre");
}

void NewMailWindow::styleAddress() {
	execCommand("formatBlock", "address");
}

void NewMailWindow::formatStrikeThrough() {
	execCommand("strikeThrough");
}

void NewMailWindow::formatAlignLeft() {
	execCommand("justifyLeft");
}

void NewMailWindow::formatAlignCenter() {
	execCommand("justifyCenter");
}

void NewMailWindow::formatAlignRight() {
	execCommand("justifyRight");
}

void NewMailWindow::formatAlignJustify() {
	execCommand("justifyFull");
}

void NewMailWindow::formatIncreaseIndent() {
	execCommand("indent");
}

void NewMailWindow::formatDecreaseIndent() {
	execCommand("outdent");
}

void NewMailWindow::formatNumberedList() {
	execCommand("insertOrderedList");
}

void NewMailWindow::formatBulletedList() {
	execCommand("insertUnorderedList");
}

void NewMailWindow::formatFontName() {
	QStringList families = QFontDatabase().families();
	bool ok = false;
	QString family = QInputDialog::getItem(this, tr("Font"), 
		tr("Select font:"), families, 0, false, &ok);

	if (ok) {
		execCommand("fontName", family);
	}
}

void NewMailWindow::formatFontSize() {
	QStringList sizes;
	sizes << "xx-small";
	sizes << "x-small";
	sizes << "small";
	sizes << "medium";
	sizes << "large";
	sizes << "x-large";
	sizes << "xx-large";

	bool ok = false;
	QString size = QInputDialog::getItem(this, tr("Font Size"), 
		tr("Select font size:"), sizes, sizes.indexOf("medium"), false, &ok);

	if(ok) {
		execCommand("fontSize", QString::number(sizes.indexOf(size)));
	}
}

void NewMailWindow::formatTextColor() {
	QColor color = QColorDialog::getColor(Qt::black, this);
	if(color.isValid()) {
		execCommand("foreColor", color.name());
	}
}

void NewMailWindow::formatBackgroundColor() {
	QColor color = QColorDialog::getColor(Qt::white, this);
	if(color.isValid()) {
		execCommand("hiliteColor", color.name());
	}
}

void NewMailWindow::insertImage() {
	QString filters;
	filters += tr("Common Graphics (*.png *.jpg *.jpeg *.gif);;");
	filters += tr("Portable Network Graphics (PNG) (*.png);;");
	filters += tr("JPEG (*.jpg *.jpeg);;");
	filters += tr("Graphics Interchange Format (*.gif);;");
	filters += tr("All Files (*)");

	QString fn = QFileDialog::getOpenFileName(this, tr("Open image..."),
				 QString(), filters);
	if(fn.isEmpty()) {
		return;
	}

	if(!QFile::exists(fn)) {
		return;
	}

	QUrl url = QUrl::fromLocalFile(fn);
	execCommand("insertImage", url.toString());
}

// shamelessly copied from Qt Demo Browser
static QUrl guessUrlFromString(const QString &string) {
	QString urlStr = string.trimmed();
	QRegExp test(QString("^[a-zA-Z]+\\:.*"));

	// Check if it looks like a qualified URL. Try parsing it and see.
	bool hasSchema = test.exactMatch(urlStr);
	if(hasSchema) {
		QUrl url(urlStr, QUrl::TolerantMode);
		if(url.isValid()) {
			return url;
		}
	}

	// Might be a file.
	if(QFile::exists(urlStr)) {
		return QUrl::fromLocalFile(urlStr);
	}

	// Might be a shorturl - try to detect the schema.
	if(!hasSchema) {
		int dotIndex = urlStr.indexOf(QLatin1Char('.'));
		if(dotIndex != -1) {
			QString prefix = urlStr.left(dotIndex).toLower();
			QString schema = (prefix == QString("ftp")) ? prefix : 
				QLatin1String("http");
			QUrl url(schema + QString("://") + urlStr, QUrl::TolerantMode);
			if(url.isValid()) {
				return url;
			}
		}
	}

	// Fall back to QUrl's own tolerant parser.
	return QUrl(string, QUrl::TolerantMode);
}

void NewMailWindow::createLink() {
	QString link = QInputDialog::getText(this, tr("Create link"),
										 "Enter URL");
	if(!link.isEmpty()) {
		QUrl url = guessUrlFromString(link);
		if(url.isValid()) {
			execCommand("createLink", url.toString());
		}
	}
}

void NewMailWindow::insertHtml() {
	if(!insertHtmlDialog) {
		insertHtmlDialog = new QDialog(this);
		if (!ui_dialog) {
			ui_dialog = new Ui_Dialog;
		}
		ui_dialog->setupUi(insertHtmlDialog);
		connect(ui_dialog->buttonBox, SIGNAL(accepted()),
				insertHtmlDialog, SLOT(accept()));
		connect(ui_dialog->buttonBox, SIGNAL(rejected()),
				insertHtmlDialog, SLOT(reject()));
	}

	ui_dialog->plainTextEdit->clear();
	ui_dialog->plainTextEdit->setFocus();
	Highlighter *hilite = new Highlighter(ui_dialog->plainTextEdit->document());

	if(insertHtmlDialog->exec() == QDialog::Accepted) {
		execCommand("insertHTML", ui_dialog->plainTextEdit->toPlainText());
	}

	delete hilite;
}

void NewMailWindow::adjustActions() {
    FOLLOW_ENABLE(ui.undoButton, QWebPage::Undo);
    FOLLOW_ENABLE(ui.redoButton, QWebPage::Redo);
    FOLLOW_ENABLE(ui.cutButton, QWebPage::Cut);
    FOLLOW_ENABLE(ui.copyButton, QWebPage::Copy);
    FOLLOW_ENABLE(ui.pasteButton, QWebPage::Paste);
    FOLLOW_CHECK(ui.boldButton, QWebPage::ToggleBold);
    FOLLOW_CHECK(ui.italicButton, QWebPage::ToggleItalic);
    FOLLOW_CHECK(ui.underlineButton, QWebPage::ToggleUnderline);

    ui.strikethroughButton->setChecked(
		queryCommandState("strikeThrough"));
    ui.numberedButton->setChecked(
		queryCommandState("insertOrderedList"));
    ui.bulletButton->setChecked(
		queryCommandState("insertUnorderedList"));
}

void NewMailWindow::adjustSource() {
    setWindowModified(true);
    sourceDirty = true;

    if (ui.tabWidget->currentIndex() == 1)
        changeTab(1);
}

void NewMailWindow::changeTab(int index) {
    if(sourceDirty && (index == 1)) {
        QString content = ui.webView->page()->mainFrame()->toHtml();
        ui.plainTextView->setPlainText(content);
        sourceDirty = false;
    }
}
