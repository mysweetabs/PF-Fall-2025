#include <stdio.h>    // Sup Fasih, hope u doing well. firstly, this code calculates one years total payment which includes the calculations of loan
                      // interest and paymnet and recursively calling it for the next year alongside the leftover loan. end conditions are if either 
                      // we complete the years or pay off the debt. for increments, the function keeps tract of it so its suitable.

float calculateRepayment(float loan, float int_rate, int yrs, int current_yr, float installment, float extra_payment)
{

    if (yrs == 0)
    {
        return 0.0f;
    }

    if (loan <= 0)
    {
        return 0.0f;
    }

    float interest = loan * (int_rate / 100.0f);
    float loan_plus_payment = loan + interest;

    float t_payment = installment + extra_payment;
    float payment = (loan_plus_payment < t_payment) ? loan_plus_payment : t_payment;

    float loan_left = loan_plus_payment - payment;

    printf("Year %d: Remaining loan = %.2f\n", current_yr, loan_left);

    return payment + calculateRepayment(loan_left, int_rate, yrs - 1, current_yr + 1, installment, extra_payment);
}

int main()
{

    float loan, int_rate, installment, extra_payment;
    int yrs;

    printf("Enter loan amount: ");
    scanf("%f", &loan);

    printf("Enter interest rate (%%): ");
    scanf("%f", &int_rate);

    printf("Enter number of yrs: ");
    scanf("%d", &yrs);

    printf("Enter yearly installment amount: ");
    scanf("%f", &installment);

    printf("Enter extra yearly payment: ");
    scanf("%f", &extra_payment);

    printf("\n--- Loan Repayment Schedule ---\n");

    float t_payment = calculateRepayment(loan, int_rate, yrs, 1, installment, extra_payment);

    printf("\nTotal Amount Paid: %.2f\n", t_payment);

    return 0;
}
