#include <stdio.h>          //This one was pretty fun to make and even more fun to use lol!
#include <string.h>         //Was testing my outputs for like 15 mins lol! You should try it out too Sire!

void encode_message(char message[]);
void decode_message(char message[]);


void encode_message(char message[]) 
{
    int i, j;
    int length = strlen(message);
    char temp;
    
    printf("\n==== Encoding rrocess ====\n");
    printf("original message: %s\n", message);
    
    for(i = 0; i < length / 2; i++) 
    {
        temp = message[i];
        message[i] = message[length - 1 - i];
        message[length - 1 - i] = temp;
    }
    
    printf("After reversal: %s\n", message);
    
    for(i = 0; i < length; i++)
    {
        message[i] = message[i] ^ (1 << 1);
        message[i] = message[i] ^ (1 << 4);
    }
    
    printf("After bit toggling: %s\n", message);
    printf("\nencoded message: %s\n", message);
}

void decode_message(char message[]) 
{
    int i, j;
    int length = strlen(message);
    char temp;
    
    printf("\n=== Decoding Process ===\n");
    printf("encoded message: %s\n", message);
    
    for(i = 0; i < length; i++) 
    {
        message[i] = message[i] ^ (1 << 1);        
        message[i] = message[i] ^ (1 << 4);
    }
    
    printf("After bit un-toggling: %s\n", message);
    
    for(i = 0; i < length / 2; i++)
    {
        temp = message[i];
        message[i] = message[length - 1 - i];
        message[length - 1 - i] = temp;
    }
    
    printf("After reversal: %s\n", message);
    printf("\ndecoded message: %s\n", message);
}

int main() {
    int choice;
    char message[500];
    
    while(1) 
    {
        printf("\n===== TCS COURIER SERVICE =====\n");
        printf("     Message encoder/decoder Tool        \n");
        printf("\n1) Encode message\n");
        printf("2) Decode message\n");
        printf("3) Exit\n");
        printf("\nplease enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        if(choice == 1)
        {
            printf("\nplease enter message to encode: ");
            fgets(message, 500, stdin);
            
            int len = strlen(message);

            if(message[len - 1] == '\n') 
            {
                message[len - 1] = '\0';
            }
            
            encode_message(message);
        }

        else if(choice == 2) 
        {
            printf("\nplease enter message to decode: ");
            fgets(message, 500, stdin);
            
            int len = strlen(message);

            if(message[len - 1] == '\n')
            {
                message[len - 1] = '\0';
            }
            
            decode_message(message);
        }

        else if(choice==3) 
        {
            printf("Exiting software.........\n");
            break;
        }

        else
        {
            printf("incorrect choice! please try again.\n");
        }
    }
    
    return 0;
}