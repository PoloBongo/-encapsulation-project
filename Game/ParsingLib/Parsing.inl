template<typename T>
void RegisterField(const std::string& key, T& field, const std::string& value) {
    try {
        field = Convert<T>(value);
    }
    catch (const std::exception& e) {
        std::cerr << "impossible de faire la conversion du champ '" << key << "' : " << e.what() << std::endl;
    }
}

template<typename T>
T Convert(const std::string& _value)
{
    static_assert(!std::is_same_v<T, T>, "Unsupported type for conversion");
}

template<>
inline int Convert<int>(const std::string& _value)
{
    return std::stoi(_value);
}

template<>
inline float Convert<float>(const std::string& _value)
{
    return std::stof(_value);
}

template<>
inline double Convert<double>(const std::string& _value)
{
    return std::stod(_value);
}

template<>
inline bool Convert<bool>(const std::string& _value)
{
    if (_value == "true") {
        return true;
    }
    else if (_value == "false") {
        return false;
    }
    else {
        throw std::invalid_argument("Valeur non valide pour un boolean");
    }
}

template<>
inline std::string Convert<std::string>(const std::string& _value)
{
    return _value;
}