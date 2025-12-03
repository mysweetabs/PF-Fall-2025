#include <stdbool.h>    //not much to tell here, tried using a bool function (hope I didnt breach any instructions)
#include <stdio.h>

bool calculate_fuel(int fuel, int consumption, int recharge, int solar_bonus, int planet, int total_planets)
{
    if (planet > total_planets)
    {
        printf("congratulations! All planets visited successfully\n");
        return true;
    }

    if (fuel <= 0)
    {
        printf("Caution! Out of fuel!\n");
        return false;
    }

    int bonus = (planet % 4 == 0) ? solar_bonus : 0;
    int remaining_fuel = fuel - consumption + recharge + bonus;
    printf("planet %d: fuel remaining = %d\n", planet, remaining_fuel);

    return calculate_fuel(remaining_fuel, consumption, recharge, solar_bonus, planet + 1, total_planets);
}

int main()
{
    int fuel = 100;
    int consumption = 20;
    int recharge = 10;
    int solar_bonus = 20;
    int total_planets = 20;

    bool success =
        calculate_fuel(fuel, consumption, recharge, solar_bonus, 1, total_planets);

    if (success)
    {
        printf("SpaceCarft can complete its journey safely\n");
    }

    else
    {
        printf("SpaceCarft cannot complete its journey\n");
    }

    return 0;
}
