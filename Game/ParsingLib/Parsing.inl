template<typename T>
void RegisterField(const std::string& key, T& field, const std::string& value) {
    try {
        if constexpr (std::is_same_v<T, int>) {
            field = std::stoi(value);
        }
        else if constexpr (std::is_same_v<T, float>) {
            field = std::stof(value);
        }
        else if constexpr (std::is_same_v<T, bool>) {
            if (value == "true") {
                field = true;
            }
            else if (value == "false") {
                field = false;
            }
            else {
                throw std::invalid_argument("Valeur non valide pour un booléen");
            }
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            field = value;
        }
        else {
            throw std::invalid_argument("Type non supporté");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors de la conversion du champ '" << key << "' : " << e.what() << std::endl;
    }
}
