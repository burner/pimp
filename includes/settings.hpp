#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <memory>
#include <vector>
#include <string>
#include <map>

#include <QSettings>

class EmailSettings {
	public:
	std::string emailadr;
	std::string username;
	std::string password;

	std::string incommingType;
	int incommingPort;
	std::string incommingUrl;
	bool incommingSASL;
	bool incommingSASLFallback;
	bool incommingTLS;
	bool incommingTLSrequired;
	std::string incommingRootpath;

	std::string outgoingType;
	int outgoingPort;
	std::string outgoingUrl;
	bool outgoingSASL;
	bool outgoingSASLFallback;
	bool outgoingTLS;
	bool outgoingTLSrequired;
	std::string outgoingRootpath;
};

class Settings {
	private:
	static Settings* inst;

	void readQSettingsFile();
	void writeQSettingsFile();
	void readEmailSettings(QSettings&);
	void writeEmailSettings(QSettings&);

	// the none static part
	std::map<std::string, EmailSettings> emailSettings;

	public:
	Settings();
	static Settings* instance();
	static std::vector<std::string> emailAddress();
	static const EmailSettings emailInfo(std::string);
	std::map<std::string, EmailSettings> getEmailSettings();
	static void readSettings();
	static void writeSettings();
	static void newEmailInfo(EmailSettings);
};
#endif
