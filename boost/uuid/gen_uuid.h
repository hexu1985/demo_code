#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

inline std::string gen_uuid()
{
    return boost::lexical_cast<std::string>(boost::uuids::random_generator()());
}
