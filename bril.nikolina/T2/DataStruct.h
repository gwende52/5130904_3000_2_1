#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>
namespace bril {
    struct DataStruct {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };
    struct DelimiterIO
    {
        char exp;
    };
    struct Raitional
    {
        std::pair<long long, unsigned long long>& ref;
    };
    struct StringIO
    {
        std::string& ref;
    };
    class iofmtguard {
    public:
        iofmtguard(std::basic_ios< char >& link);
        ~iofmtguard();
    private:
        std::basic_ios< char >& link_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, Raitional&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
