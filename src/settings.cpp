#include <QMessageBox>

#include <settings.hpp>
#include <debug.hpp>
#include <exception.hpp>

Settings* Settings::inst = NULL;

Settings* Settings::instance() {
	if(Settings::inst == NULL) {
		Settings::inst = new Settings;
	}
	inst->readQSettingsFile();
	return Settings::inst;
};

Settings::Settings() {
	LOG();
	this->readQSettingsFile();
}

std::vector<std::string> Settings::emailAddress() {
	auto ins = Settings::instance();
	std::vector<std::string> rslt;
	
	for(auto it : ins->emailSettings) {
		rslt.push_back(it.first);
	}
	return rslt;
}

std::map<std::string, EmailSettings> Settings::getEmailSettings() {
	return emailSettings;
}

const EmailSettings Settings::emailInfo(std::string adr) {
	auto ins = Settings::instance();
	auto it = ins->getEmailSettings().find(adr);
	if(it != ins->getEmailSettings().end()) {
		return it->second;
	} else {
		std::vector<ptype> args = { adr };
		std::string msg = format(
			"trying to access email settings for %s which is not present",
			args);
		WARN(msg);
		throw OutOfBoundException(msg);
	}
	assert(false);
}

void Settings::readEmailSettings(QSettings& settings) {
	LOG();
	unsigned size = settings.beginReadArray("emailSettings");
	for(unsigned i = 0; i < size; i++) {
		settings.setArrayIndex(i);
		EmailSettings tmp;
		
		//general
		tmp.emailadr = settings.value("emailadr").toString().toStdString();
		tmp.username = settings.value("username").toString().toStdString();
		tmp.password = settings.value("password").toString().toStdString();

		// incomming
		tmp.incommingType = settings.value("incommingType").toString().
			toStdString();
		tmp.incommingPort = settings.value("incommingPort").
			toInt();
		tmp.incommingTLS = settings.value("incommingTLS").toBool();
		tmp.incommingTLSrequired = settings.value("incommingTLSrequired").
			toBool();
		tmp.incommingSASL = settings.value("incommingSASL").toBool();
		tmp.incommingSASLFallback = settings.value("incommingSASLFallback").
			toBool();

		// outgoing
		tmp.outgoingType = settings.value("outgoingType").toString().
			toStdString();
		tmp.outgoingPort = settings.value("outgoingPort").
			toInt();
		tmp.outgoingTLS = settings.value("outgoingTLS").toBool();
		tmp.outgoingTLSrequired = settings.value("outgoingTLSrequired").
			toBool();
		tmp.outgoingSASL = settings.value("outgoingSASL").toBool();
		tmp.outgoingSASLFallback = settings.value("outgoingSASLFallback").
			toBool();

		emailSettings.insert(std::make_pair(tmp.emailadr, tmp));
	}
	settings.endArray();
}

void Settings::writeEmailSettings(QSettings& settings) {
	settings.beginWriteArray("emailSettings");
	auto it = emailSettings.begin();
	for(size_t i = 0; it != emailSettings.end() &&
			i < emailSettings.size(); i++) {
		auto tmp = it->second;
		settings.setValue("emailadr", QString::fromStdString(tmp.emailadr));
		settings.setValue("username", QString::fromStdString(tmp.username));
		settings.setValue("password", QString::fromStdString(tmp.password));

		// incomming
		settings.value("incommingType", QString::fromStdString(
			tmp.incommingType)
		);
		settings.value("incommingPort", QString(tmp.incommingPort));
		settings.value("incommingTLS", tmp.incommingTLS ? "true" : "false");
		settings.value("incommingTLSrequired", tmp.incommingTLSrequired ? 
			"true" : "false");
		settings.value("incommingSASL", tmp.incommingSASL ? "true" : "false");
		settings.value("incommingSASLFallback", tmp.incommingSASLFallback ? 
			"true" : "false");

		// outgoing
		settings.value("outgoingType", QString::fromStdString(
			tmp.outgoingType)
		);
		settings.value("outgoingPort", QString(tmp.outgoingPort));
		settings.value("outgoingTLS", tmp.outgoingTLS ? "true" : "false");
		settings.value("outgoingTLSrequired", tmp.outgoingTLSrequired ?  "true" 			: "false");
		settings.value("outgoingSASL", tmp.outgoingSASL ?  "true" : "false");
		settings.value("outgoingSASLFallback", tmp.outgoingSASLFallback ? 
			"true" : "false");
	}
	settings.endArray();
}

void Settings::readQSettingsFile() {
	QSettings settings;
	this->readEmailSettings(settings);
}

void Settings::writeQSettingsFile() {
	QSettings settings;
	this->writeEmailSettings(settings);
}

void Settings::readSettings() {
	auto ins = Settings::instance();
	ins->readQSettingsFile();
}

void Settings::writeSettings() {
	auto ins = Settings::instance();
	ins->writeQSettingsFile();
	QSettings settings;
	settings.sync();
}

void Settings::newEmailInfo(EmailSettings ne) {
	auto ins = Settings::instance();
	auto exists = ins->emailSettings.find(ne.emailadr);
	if(exists != ins->emailSettings.end()) {
		QMessageBox msgBox;
		msgBox.setText(QObject::tr(
		   "EMail acocunt with that name allready present") );
		msgBox.setIcon( QMessageBox::Critical );
		msgBox.exec();
		return;
	}
	ins->emailSettings.insert(std::make_pair(ne.emailadr, ne));
	ins->writeQSettingsFile();
	ins->readQSettingsFile();
}
