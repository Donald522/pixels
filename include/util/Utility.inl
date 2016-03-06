

template <typename T>
std::string ToString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}
