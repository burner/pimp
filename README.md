# pimp : personal information manager pimp
The general idea is to create a pim that combines all kind of information
exchange programs into one program. The approach is to write as little code as
possible and use existing libraries whenever possible. No new all enclosing
backend should be created. We do not want akonadi2. Pimp will use qt as a gui
library. The whole program will be controllable through a keyboard. Think Vim
not Emacs. The language used is cpp0x. Raw pointer are to be avoided as much
as possible. This means shared_ptr. To make the code somewhat nicer pimp will
be compiled with -Wall and Werror. The gui will be created with the qt
designer. Headers have the ending .hpp and are placed in the includes
directory. Source files have the ending .cpp and are placed in the src
directory. Ui files are placed in the ui directory. Resources are placed in
the resource directory.

* summary: A overview page showing the most important information of all the
other enteties
* mail:
* calendar:
* contacts:
* instant messanger:
* irc:
* todo:
* rss-atom:
