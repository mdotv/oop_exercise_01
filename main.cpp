#include <iostream>
#include <string>
#include <limits>
#include <cmath>

class Angle
{
    public:
        Angle ()
        {
            m_degrees = 0;
            m_minutes = 0;
        }
        Angle (const int& minutes)
        {
            int sign{};
            if (abs(minutes) >= 60) {
                m_degrees = minutes / 60;
                m_minutes = abs(minutes) % 60;
            }
            else {
                m_degrees = 0;
                m_minutes = minutes % 60;
            }
        }
        void setAngle()
        {
            std::cout << "Enter angle degrees: ";
            int degrees{};
            std::cin >> degrees;
            m_degrees = degrees;
            std::cout << "Enter angle minutes: ";
            int minutes{};
            std::cin >> minutes;
            if (minutes >= 60) {
                if (m_degrees < 0)
                    m_degrees -= minutes / 60;
                else 
                    m_degrees += minutes / 60;
                m_minutes = minutes % 60;
            }
            else
                m_minutes = minutes;
            if (m_degrees < 0 || (m_minutes < 0 && m_degrees != 0)) {
                m_minutes = abs(minutes);
                m_degrees = -abs(degrees);
            }
        }
        int toMinutes()
        {
            int minutes{};
            if (m_degrees == 0)
                minutes = m_minutes;
            else if (m_degrees < 0)
                minutes = m_degrees * 60 - m_minutes;
            else 
                minutes = m_degrees * 60 + m_minutes;
            return minutes;
        }
        Angle divideAngle(const int& div, int& seconds)
        {
            int minutes{ toMinutes() };
            seconds = minutes * 60 / div;
            minutes = seconds / 60;
            seconds = abs(seconds) % 60;
            Angle quotient{ minutes };
            return quotient;
        }
        Angle subtractAngle(Angle& b)
        {
            int minutes{ toMinutes() - b.toMinutes() };
            Angle diff{ minutes };
            return diff;
        }
        Angle addAngle(Angle& b) 
        {

            int minutes{ toMinutes() + b.toMinutes() };
            Angle sum{ minutes };
            return sum;
        }
        void angleToRange()
        {
            long minutes{};
            if (m_degrees >= 0)
                minutes = m_degrees * 60 + m_minutes;
            else 
                minutes = m_degrees * 60 - m_minutes; 
            int max{ 360 * 60 };
            if (minutes < 0) {
                minutes = abs(minutes);
                while (minutes > max)
                    minutes -= max;
                minutes = max - minutes;
            }
            else 
                while (minutes > max)
                    minutes -= max;
            m_degrees = minutes / 60;
            m_minutes = minutes % 60;
        }
        bool isGreater(const Angle& b, bool& isEqual)
        {
            bool greater{ false };
            if (m_degrees == b.m_degrees) {
                if (m_minutes == b.m_minutes)
                    isEqual = true;
                else if (m_minutes > b.m_minutes)
                    greater = true;
            }
            else if (m_degrees > b.m_degrees)
                greater = true;
            return greater;
        }
        double getRad()
        {
            double radians{};
            if (m_minutes < 0)
                radians = M_PI * ((static_cast<double>(m_minutes) / 60.0) / 180.0);
            else if (m_degrees < 0)
                radians = M_PI * ((static_cast<double>(m_degrees) - static_cast<double>(m_minutes) / 60.0) / 180.0);
            else 
                radians = M_PI * ((static_cast<double>(m_degrees) + static_cast<double>(m_minutes) / 60.0) / 180.0);
            return radians;
        }
        double getCosec()
        {
            angleToRange();
            double cosecant{ 1.0 / sin(getRad()) };
            if (fabs(cosecant) > 0.1e6)
                cosecant = NAN;
            return cosecant;
        }
        double getSec()
        {
            angleToRange();
            double secant{ 1.0 / cos(getRad()) };
            if (fabs(secant) > 0.1e6)
                secant = NAN;
            return secant;
        }
        double getCtg()
        {
            angleToRange();
            double cotangens{ 1.0 / tan(getRad()) };
            if (fabs(cotangens) < 1.0e-6)
                cotangens = 0;
            else if (fabs(cotangens) > 0.1e6)
                cotangens = NAN;
            return cotangens;
        }
        double getTg()
        {
            angleToRange();
            double tangens{ tan(getRad()) };
            if (fabs(tangens) < 1.0e-6)
                tangens = 0;
            else if (fabs(tangens) > 0.1e6)
                tangens = NAN;
            return tangens;
        }
        double getCos()
        {  
            angleToRange();
            double cosinus{ cos(getRad()) };
            if (fabs(cosinus) < 1.0e-6)
                cosinus = 0;
            return cosinus;
        }
        double getSin()
        {
            angleToRange();
            double sinus{ sin(getRad()) };
            if (fabs(sinus) < 1.0e-6)
                sinus = 0;
            return sinus;
        }
        void printAngle()
        {
            std::cout << m_degrees << '\370' << m_minutes << '\'';
        }
    private:
        int m_degrees{}, m_minutes{};
};

void funInterface()
{
    system("cls");
    int choice{ 0 };
    std::string message{ "Enter number: " };
    std::cout << "Trigonometric functions\n";
    do {
        std::cout << 
                 "----------------------------\n" <<
                 "1. sin x                   |\n" <<
                 "2. cos x                   |\n" <<
                 "3. tg x                    |\n" <<
                 "4. ctg x                   |\n" <<
                 "5. sec x                   |\n" <<
                 "6. cosec x                 |\n" <<
                 "0. return                  |\n" <<
                 "----------------------------\n" << 
                 message << '\n';
        if (!(std::cin >> choice)) {
            choice = -1;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (choice) {
            case 1 : {
                system("cls");
                std::cout << "sin x (q for quit)\n----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nangle = ";
                a.printAngle();
                Angle b = a;
                a.angleToRange();
                bool equal{ false };
                a.isGreater(b, equal);
                if (!equal) {
                    std::cout << " = ";
                    a.printAngle();
                }
                std::cout << "\nsin("; 
                a.printAngle();
                std::cout << ") = " << a.getSin() << '\n'; 
                break;
            }
            case 2 : {
                system("cls");
                std::cout << "cos x (q for quit)\n----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nangle = ";
                a.printAngle();
                Angle b = a;
                a.angleToRange();
                bool equal{ false };
                a.isGreater(b, equal);
                if (!equal) {
                    std::cout << " = ";
                    a.printAngle();
                }
                std::cout << "\ncos("; 
                a.printAngle();
                std::cout << ") = " << a.getCos() << '\n';
                break;
            }
            case 3 : {
                system("cls");
                std::cout << "tg x (q for quit)\n----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nangle = ";
                a.printAngle();
                Angle b = a;
                a.angleToRange();
                bool equal{ false };
                a.isGreater(b, equal);
                if (!equal) {
                    std::cout << " = ";
                    a.printAngle();
                }
                std::cout << "\ntg("; 
                a.printAngle();
                std::cout << ") = " << a.getTg() << '\n';
                break;
            }
            case 4 : {
                system("cls");
                std::cout << "ctg x (q for quit)\n----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nangle = ";
                a.printAngle();
                Angle b = a;
                a.angleToRange();
                bool equal{ false };
                a.isGreater(b, equal);
                if (!equal) {
                    std::cout << " = ";
                    a.printAngle();
                }
                std::cout << "\nctg("; 
                a.printAngle();
                std::cout << ") = " << a.getCtg() << '\n';
                break;
            }
            case 5 : {
                system("cls");
                std::cout << "sec x (q for quit)\n----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nangle = ";
                a.printAngle();
                Angle b = a;
                a.angleToRange();
                bool equal{ false };
                a.isGreater(b, equal);
                if (!equal) {
                    std::cout << " = ";
                    a.printAngle();
                }
                std::cout << "\nsec("; 
                a.printAngle();
                std::cout << ") = " << a.getSec() << '\n';
                break;
            }
            case 6 : {
                system("cls");
                std::cout << "cosec x (q for quit)\n----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nangle = ";
                a.printAngle();
                Angle b = a;
                a.angleToRange();
                bool equal{ false };
                a.isGreater(b, equal);
                if (!equal) {
                    std::cout << " = ";
                    a.printAngle();
                }
                std::cout << "\ncosec("; 
                a.printAngle();
                std::cout << ") = " << a.getCosec() << '\n';
                break;
            }
            case 0 : {
                system("cls");
                break;
            }
            default :
                system("cls");
                message = "Please, enter 0-6 number";
                break;
        }
    } while (choice != 0);
}

void interface(void)
{
    system("cls");
    int choice{ 0 };
    std::string message{ "Enter number: " };
    do {
        std::cout << 
                 "----------------------------\n" <<
                 "1. To radians conversion   |\n" <<
                 "2. Angle to range 0-360    |\n" <<
                 "3. Add angles              |\n" <<
                 "4. Subtract angles         |\n" <<
                 "5. Divide angle            |\n" <<
                 "6. Trigonometric functions |\n" <<
                 "7. Compare angles          |\n" << 
                 "0. Quit                    |\n" <<
                 "----------------------------\n" << 
                 message << '\n';
        if (!(std::cin >> choice)) {
            choice = -1;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (choice) {
            case 1 : {
                system("cls");
                std::cout << "To radians conversion (q for return)\n" <<
                             "----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "Angle = ";
                a.printAngle(); 
                std::cout << " = " << a.getRad() << " rad\n";
                break;
            }
            case 2 : {
                system("cls");
                std::cout << "Angle to range 0-360 (q for return)\n" <<
                             "----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "Angle = ";
                a.printAngle();
                a.angleToRange();
                std::cout << "\nAngle in range = ";
                a.printAngle();
                std::cout << '\n';
                break;
            }
            case 3 : {
                system("cls");
                std::cout << "Add angles (q for return)\n" <<
                             "----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nFirst angle = ";
                a.printAngle();
                std::cout << "\n----------------------------\n";
                Angle b{};
                b.setAngle();
                std::cout << "\nSecond angle = ";
                b.printAngle();
                std::cout << "\n----------------------------\n";
                Angle sum{ a.addAngle(b) };
                std::cout << "Sum = ";
                sum.printAngle();
                std::cout << '\n';
                break;
            }
            case 4 : {
                system("cls");
                std::cout << "Subtract angles (q for return)\n" <<
                             "----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nFirst angle = ";
                a.printAngle();
                std::cout << "\n----------------------------\n";
                Angle b{};
                b.setAngle();
                std::cout << "\nSecond angle = ";
                b.printAngle();
                std::cout << "\n----------------------------\n";
                Angle diff{ a.subtractAngle(b) };
                std::cout << "Difference = ";
                diff.printAngle();
                std::cout << '\n';
                break;
            }
            case 5 : {
                system("cls");
                std::cout << "Divide angle  (q for return)\n" <<
                             "----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "Enter divisor: ";
                int div{};
                if (!(std::cin >> div))
                    break;
                while (div == 0) {
                    std::cout << "Error! Divisor can't be '0'!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter divisor: ";
                    if (!(std::cin >> div))
                        break;
                }
                if (div == 0)
                    break;
                std::cout << "\nAngle = ";
                a.printAngle();
                std::cout << "\nDivisor = " << div << '\n';
                int seconds{};
                Angle quotient{ a.divideAngle(div, seconds) };
                std::cout << "Quotient = ";
                quotient.printAngle();
                std::cout << seconds << "\"\n";
                break;
            }
            case 6 : {
                funInterface();
                break;
            }
            case 7 : {
                system("cls");
                std::cout << "Compare angles (q for return)\n" <<
                             "----------------------------\n";
                Angle a{};
                a.setAngle();
                std::cout << "\nFirst angle = ";
                a.printAngle();
                std::cout << "\n----------------------------\n";
                Angle b{};
                b.setAngle();
                std::cout << "\nSecond angle = ";
                b.printAngle();
                std::cout << "\n----------------------------\n";
                bool isEqual{ false };
                if (a.isGreater(b, isEqual))
                    std::cout << "First angle is greater\n";
                else {
                    if (isEqual)
                        std::cout << "Angles are equal\n"; 
                    else    
                        std::cout << "Second angle is greater\n";
                }
                break;
            }
            case 0 :
                break;
            default :
                system("cls");
                message = "Please, enter 0-7 number";
                break;
        }
    } while (choice != 0);
}

int main()    
{
    interface();
    system("cls");

    return 0;
}