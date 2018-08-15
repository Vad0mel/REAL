#include "Version.h"

#include <regex>
#include <sstream>

using namespace miniant::WasapiLatency;

std::string Version::ToString() const {
    std::stringstream ss;
    ss << m_major << '.' << m_minor << '.' << m_patch;
    return ss.str();
}

bool Version::operator< (const Version& rhs) const {
    if (m_major != rhs.m_major)
        return m_major < rhs.m_major;

    if (m_minor != rhs.m_minor)
        return m_minor < rhs.m_minor;

    return m_patch < rhs.m_patch;
}

bool Version::operator> (const Version& rhs) const {
    return rhs < *this;
}

bool Version::operator==(const Version& rhs) const {
    return m_major == rhs.m_major && m_minor == rhs.m_minor && m_patch == rhs.m_patch;
}

bool Version::operator!=(const Version& rhs) const {
    return !(*this == rhs);
}

bool Version::operator<=(const Version& rhs) const {
    return *this == rhs || *this < rhs;
}

bool Version::operator>=(const Version& rhs) const {
    return *this == rhs || *this > rhs;
}

std::optional<Version> Version::Parse(const std::string& versionString) {
    std::regex pattern(R"(^(\d+)\.(\d+)\.(\d+)$)");
    std::smatch matches;
    if (!std::regex_match(versionString, matches, pattern))
        return {};

    int major = std::stoi(matches[1].str());
    int minor = std::stoi(matches[2].str());
    int patch = std::stoi(matches[3].str());
    if (major > UINT16_MAX || minor > UINT16_MAX || patch > UINT16_MAX)
        return {};

    return { Version(
        static_cast<uint16_t>(major),
        static_cast<uint16_t>(minor),
        static_cast<uint16_t>(patch)) };
}