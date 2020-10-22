namespace machine
{
    void Machine::make_convertation(std::istream& is) {
        std::string up_line, mid_line, low_line;

	    while(std::getline(is, up_line, '\n') &&
              std::getline(is, mid_line, '\n') &&
              std::getline(is, low_line, '\n')) 
        {	
            std::stringstream number = _get_number(up_line,
                                                   mid_line,
                                                   low_line);

            result << number.str();
            result << (_ill_flag ? "\tILL\n" : 
                                 _is_valid(number) ? "\n" : "\tERR\n");

            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip blank line

            _ill_flag = false;
        }
    }


    std::stringstream Machine::_get_number(std::string& up_line,
                                           std::string& mid_line,
                                           std::string& low_line) 
    {
        std::stringstream number;

        std::size_t min_len = std::min({up_line.length(),
                                        mid_line.length(),
                                        low_line.length()});

        min_len /= 3;

        std::size_t digit_count = min_len;
        while (digit_count > 0) {
            std::string digit_str = up_line.substr(0, 3) + 
                                    mid_line.substr(0, 3) + 
                                    low_line.substr(0, 3);


            up_line.erase(0, 3);
            mid_line.erase(0, 3);
            low_line.erase(0, 3);                                        

            auto digit_iter = _digit_map.find(digit_str);

            if (digit_iter != _digit_map.end()) {
                number << digit_iter->second;                              
            }
            else {
                _ill_flag = true;
                number << '?';
            }

            digit_count --;
        }

        if (min_len < 9) {
            _ill_flag = true;
            for (std::size_t i = min_len; i < 9; i++) {
                number << '?';
            }
        }

        return number;
    }


    bool Machine::_is_valid(std::stringstream& number) {
        std::size_t checksum = 0;
        short koeff = 9;

        while (!number.eof()) {
            checksum += (number.get() - 48) * koeff;
            koeff--;
        }
        
        return checksum % 11 == 0;
    }


    std::istream& operator >> (std::istream& is, Machine& mc) {	
        if (!is.good()) {
            throw std::runtime_error("operator<< error!");
        }

        mc.make_convertation(is);

        return is;
    }


    std::ostream& operator << (std::ostream& os, const Machine& mc) {	
        if (!os.good()) {
            throw std::runtime_error("operator<< error!");
        }

        os << mc.result.str();

        return os;
    }
    
} // namespace machine
