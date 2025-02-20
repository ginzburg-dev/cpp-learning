
#include <iostream>
#include <random>
#include <chrono>
#include <limits>

namespace Random
{
    std::mt19937 generate()
    {
        std::random_device rd{};
        std::seed_seq ss{ static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count() ),
            rd(), rd(), rd(), rd(), rd(), rd(), rd() };

        return std::mt19937{ ss };
    }

    std::mt19937 mt{ Random::generate() };

    int get(int min, int max)
    {
        return std::uniform_int_distribution<>{min, max}(mt);
    }
}

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

bool clearFailedExtraction()
{
    if ( !std::cin )
    {
        if ( std::cin.eof() )
        {
            std::abort();
        }

        std::cin.clear();
        ignoreLine();

        return true;
    }

    return false;
}

int getValue(int min, int max)
{
    while (true)
    {
        int x{};
        std::cin >> x;

        if ( clearFailedExtraction() )
        {
            std::cerr << "Oops, that input is invalid. Please try again\n";
            continue;
        }

        ignoreLine();

        if ( (x < min) || (x > max) )
        {
            std::cerr << "Oops, that input is invalid. It should be in " << min << " - " 
                << max << " range. Please try again\n";
            continue;
        }

        return x;
    }

}

bool playLoHi(int guesses, int min, int max)
{
    std::cout << "Let's play a game. I'm thinking of a number between " << 1 <<" and " << 100 << ". You have " 
    << guesses <<" tries to guess what it is.\n";

    int number{ Random::get(min, max) };

    for (int i{ 1 }; i <= guesses; ++i)
    {
        std::cout << "Guess #" << i << ": ";

        int guess{ getValue(min, max) };

        if ( guess > number)
            std::cout << "Your guess is too high.\n";
        else if ( guess < number )
            std::cout << "Your guess is too low.\n";
        else if ( guess == number )
        {
            std::cout << "Correct! You win!\n";
            return true;
        }
    }

    std::cout << "Sorry, you lose. The correct number was " << number << '\n';
    return false;
}

bool playAgain()
{
    while (true)
    {
        std::cout << "Would you like to play again (y/n) ?: ";

        char c{};
        std::cin >> c;

        if ( !clearFailedExtraction() )
            ignoreLine();

        switch (c)
        {
        case 'n': return false;
        case 'y': return true;
        default: 
            std::cerr << "Oops, that input is invalid. Please try again\n";
        }
    }
}

int main()
{
    constexpr int min{ 1 };
    constexpr int max{ 100 };
    constexpr int guesses{ 7 };

    do
    {
        playLoHi(guesses, min, max);
    } while ( playAgain() );
    

    return 0;
}
