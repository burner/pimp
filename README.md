# pimp : personal information manager pimp
The general idea is to create a pim that combines all kind of information
exchange programs into one program. The approach is to write as little code as
possible and use existing libraries whenever possible. No new all enclosing
backend should be created. We do not want akonadi2. Pimp will use qt as its
gui library. The whole program will be controllable through a keyboard. Think
poweruser. The language used is cpp11. Raw pointer are to be avoided. This
means shared\_ptr. Exceptions are the way for error handling. To make the
code somewhat nicer pimp will be compiled with -Wall and -Werror. The gui will
be created with the qt designer, simply less code. A good spell correction
library will be integraded. Headers have the ending .hpp and are placed in the
includes directory. Source files have the ending .cpp and are placed in the
src directory. Ui files are placed in the ui directory. Resources are placed
in the resource directory. 

## Elements

### Summary: 
* Aim: A overview page showing the most important information of all the
other entities. The idea is to have quick access to all new mails, feeds and
so on. 
* Implementation: Keeping things simple is the priority. A interface with a
method returning a widget should be enough.

### Mail:
* Aim: Just another email client. Just take the arithmetic middle of all
features of existing email clients.
* Implementation: Libvmime should be used as it brings most needed
functionality like imap, smtp, and pop3. Maildir should be used for storage.

### Calendar:
* Aim: Just another calendar. Think Sunbird.
* Implementation: Choose any good iCalendar and caldav library. All features 
of the google calendar should as well, maybe libgcal is needed as well. If
more than one calendar lib is needed a simple abstraction should be
implemented.

### Contacts:
* Aim: Just another contact manager. This should provide an easy interface for
the mail part to get addresses and such.
* Implementation: Don't know yet.

### Instant messenger:
* Aim: Think pidgin.
* Implementation: Think pidgin again, libpurple.

### Irc:
* Aim: Think your favourite irc client.
* Implementation: Maybe libpurplem more research needed.

### Todo:
* Aim: A separate todo list that should be synchronize-able.
* Implementation: Don't know yet.

### Rss-atom:
* Aim: Simple rss reading, nothing really fancy.
* Implementation: Libmrss 

## Coding

### Style
* 78 character lines
* Hold functions short
* Tabs for indent, tabs are four spaces long
* Curly brackets for every for while do if
* Curly brackets start at the end of the line, not at the next line
* No spaces between the keyword and the opening parenthesis
* Someday all functions should have doxygen comments
* Exceptions

### Guideline
* Use the debug.hpp header and its typesafe printf log and warn function
* Throw exceptions on misbehaving code.
* On top of qt and any application specific library boost can be used but only
if no stl option is present.
