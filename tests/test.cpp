/*
** EPITECH PROJECT, 2021
** nanotekspice
** File description:
** test
*/

#include <ostream>                                                                                                                                                                                       
#include <iostream>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

class OSRedirector {
    private:
        std::ostringstream _oss;
        std::streambuf *_backup;
        std::ostream &_c;

    public:
        OSRedirector(std::ostream &c) : _c(c) {
            _backup = _c.rdbuf();
            _c.rdbuf(_oss.rdbuf());
        }

        ~OSRedirector() {
            _c.rdbuf(_backup);
        }

        const std::string getContent() {
            _oss << std::flush;
            return _oss.str();
        }
};

Test(ex01, ex01)
{
    cr_assert_eq(1, 1);
}