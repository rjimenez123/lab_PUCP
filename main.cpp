#include <stdio.h>
#include <stdlib.h>
#include "my_functions.h"

#define NAME_LONGITUDE 25

using namespace std;

int main()
{
    int items_read, mes, anho, dia, hh, mm, ss;
    int movements_counter, op_sign, name_length, num_page;
    double initial_ammount, op_ammount;
    char c, aux;
    bool init_char = true, is_first_movement = true;

    printf("ESTADO DE CUENTAS DEL BANCO \"PITUFO GRUÑON\"\n");
    print_line(100, '=');
    printf("\n");

    while (1) {
        items_read = scanf("%d/%d/%d", &dia, &mes, &anho);
        if (items_read == EOF) {
            print_line(100, '=');
            printf("\nRESUMEEEEEEEEEEEN:\n");
            print_line(100, '=');
            printf("\n");
            break;
        }
        if (items_read == 0) { // Es D/R o codigo de cliente
            c = getchar(); aux = getchar();
            if (aux == ' ' || aux == '\n') { // Es D/R
                op_sign = (c == 'R' ? -1 : +1);
            } else { // Es un codigo de un nuevo cliente
                printf("CODIGO DE CUENTA%9cCLIENTE%18cSALDO INICIAL\n", ' ', ' ');
                printf("%4c", ' ');
                putchar(c); putchar(aux);
                while( (c = getchar()) != ' ')
                    putchar(c);
                printf("%15c", ' ');
                scanf("%*d"); // leo los espacios locos
                while( (c = getchar()) != ' ') { // leo y escribo el nombre
                    if (c == '/') {
                        printf(" ");
                        continue;
                    }
                    putchar(c);
                    name_length++;
                }
                for (int i = 0; i < NAME_LONGITUDE - name_length; i++)
                    printf(" ");
                scanf("%lf", &initial_ammount);
                printf("%15.2lf\n", initial_ammount);
                print_line(100, '=');
                printf("%69cPagina %2d", ' ', num_page);
                printf("\n\n");
                printf("FECHA%10c  HORA%9c RETIROS%7cDEPOSITOS%6c  SALDO%8c  OBSERVACION\n", ' ',  ' ',  ' ',  ' ',  ' ');
                print_line(100, '-');
                printf("\n");
            }
        }

        if (items_read == 3) { // Es una fecha
            printf("%2d/%2d/%4d", dia, mes, anho);
            printf("%5c", ' ');
            is_first_movement = true;
        }

        if (items_read == 1) { // Es una hora y un nuevo movimiento
            movements_counter++;
            hh = dia;
            scanf(":%2d:%2d", &mm, &ss);
            if (is_first_movement) {
                printf("%2d:%2d:%2d", hh, mm, ss);
                printf("%7c", ' ');
                is_first_movement = false;
            } else {
                printf("%15c%2d:%2d:%2d", ' ', hh, mm, ss);
                printf("%7c", ' ');
            }

            scanf("%lf", &op_ammount);
            initial_ammount += op_ammount*op_sign;
            if (op_sign == -1) { // Es un retiro
                printf("%8.2lf%22c", op_ammount, ' ');
            } else { // Es un deposito
                printf("%15c%8.2lf%7c", ' ', op_ammount, ' ');
            }

            printf("%8.2lf%7c", initial_ammount, ' ');

            if (initial_ammount < 0)
                printf("SOBREGIRO%16c\n", ' ');
            else if (initial_ammount < 3000)
                printf("BAJO EL MINIMO%11c\n", ' ');

            if (movements_counter == 20) {
                num_page++;
                print_line(100, '-');
                printf("\n");
                printf("%69cPagina %2d", ' ', num_page);
                printf("\n\n");
                printf("FECHA%10c  HORA%9c RETIROS%7cDEPOSITOS%6c  SALDO%8c  OBSERVACION\n", ' ',  ' ',  ' ',  ' ',  ' ');
                print_line(100, '-');
                printf("\n");
            }
        }
    }
    return 0;
}
