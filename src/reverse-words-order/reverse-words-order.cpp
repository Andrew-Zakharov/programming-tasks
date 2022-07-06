#include <iostream>
#include <vector>
#include <string>


enum StateType{
    q0 = 0,
    q1
};

class StateMachine{
    public:
        StateMachine()
        {
            
        };

        ~StateMachine(){

        };

        void process(const std::string& source){
            data.emplace_back();
            for(const char& c : source){
                switch(state){
                    case q0:{
                        if(c == ' '){
                            toState(StateType::q1);
                        }
                        else{
                            data.back().push_back(c);
                        }
                    }break;

                    case q1:{
                        if(c != ' '){
                            data.emplace_back(1, c);
                            toState(StateType::q0);
                        }
                    }break;
                }
            }
        }

        void toState(StateType state){
            this->state = state;
        }

        std::vector<std::vector<char>> get_data(){
            return data;
        }

        std::string get_reverse_order_string(){
            std::string reverse_order;

            for(size_t i = data.size() - 1; i >= 1; i--){
                std::vector<char> word = data.at(i);

                reverse_order.append(word.begin(), word.end());

                reverse_order += ' ';
            }

            reverse_order.append(data[0].begin(), data[0].end());

            return reverse_order;
        }

    private:
        StateType state = q0;
        std::vector<std::vector<char>> data;
};

void print_vector(const std::vector<char>& v){
    for(const char& s : v){
        std::cout << s << std::endl;
    }
}

int main(){

    std::string s = "This is a string";
    StateMachine m;

    std::cout << "String before processing: " << s << std::endl;

    m.process(s);

    std::cout << "String after processing: " << m.get_reverse_order_string() << std::endl;

    //print_vector(m.get_data());

    return 0;
}