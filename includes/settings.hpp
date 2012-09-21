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
	std::string type;
	unsigned short port;
};

class Settings {
	private:
	static Settings* inst;

	void readQSettingsFile();
	void readEmailSettings(QSettings&);

	// the none static part
	std::map<std::string, EmailSettings> emailSettings;

	public:
	Settings();
	static Settings* instance();
	static std::vector<std::string> emailAddress();
	static const EmailSettings emailInfo(std::string);
	std::map<std::string, EmailSettings> getEmailSettings();
};
#endif
