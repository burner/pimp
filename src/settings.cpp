#include <settings.hpp>
#include <debug.hpp>
#include <exception.hpp>

Settings* Settings::inst = NULL;

Settings* Settings::instance() {
	if(Settings::inst == NULL) {
		Settings::inst = new Settings;
	}
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
		//std::vector<ptype> args = { adr };
		std::string msg = format(
			"trying to access email settings for %s which is not present",
			adr);
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
		tmp.emailadr = settings.value("emailAdr").toString().toStdString();
		tmp.username = settings.value("username").toString().toStdString();
		tmp.password = settings.value("password").toString().toStdString();
		tmp.type = settings.value("type").toString().toStdString();
		tmp.port = static_cast<short>(settings.value("port").toInt());
		emailSettings.insert(std::make_pair(tmp.emailadr, tmp));
	}
	settings.endArray();
}

void Settings::readQSettingsFile() {
	QSettings settings;
	this->readEmailSettings(settings);
}
