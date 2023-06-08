#include <nox/vector>
#include <nox/exception>

int main(void)
{
    nox::__throw_exception("main()");

    nox::vector<int> v;

    int x = v.at(0);

    return 0;
}