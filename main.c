#include <stdio.h>

int main(void)
{
    int memory[256] = {0};
    int cpu_state[8] = {0};
    int n = 0, op, addr, pc;

    /* Команды и данные находятся в общей памяти, а cpu_state хранит состояние процессора. */
    while (n < 256 && scanf("%d", &memory[n]) == 1)
        n++;

    if (n <= 6) {
        printf("Недостаточно данных\n");
        return 1;
    }

    cpu_state[0] = 6;
    cpu_state[3] = memory[0];

    while (cpu_state[4] == 0) {
        pc = cpu_state[0];
        if (pc < 0 || pc >= n) {
            cpu_state[5] = 1;
            break;
        }

        op = memory[pc];
        cpu_state[2] = op;
        addr = -1;

        if (op == 3 || op == 4 || op == 5) {
            if (pc + 1 >= n) {
                cpu_state[5] = 1;
                break;
            }
            addr = memory[pc + 1];
            if (addr < 0 || addr >= n) {
                cpu_state[5] = 1;
                break;
            }
        }

        switch (op) {
            case 0:
                cpu_state[4] = 1;
                break;
            case 1:
                cpu_state[1]++;
                cpu_state[0]++;
                break;
            case 2:
                cpu_state[1]--;
                cpu_state[0]++;
                break;
            case 3:
                cpu_state[1] += memory[addr];
                cpu_state[0] += 2;
                break;
            case 4:
                cpu_state[0] = addr;
                break;
            case 5:
                if (cpu_state[1] == 0)
                    cpu_state[0] = addr;
                else
                    cpu_state[0] += 2;
                break;
            default:
                cpu_state[5] = 2;
                break;
        }
        printf("pc=%d, op=%d, operand=%d, acc=%d\n", pc, op, addr, cpu_state[1]);
        if (cpu_state[5] != 0)
            break;
    }

    if (cpu_state[5] != 0) {
        printf("Ошибка %d\n", cpu_state[5]);
        cpu_state[4] = 1;
    }
    printf("ACC=%d, ошибка=%d\n", cpu_state[1], cpu_state[5]);
    return cpu_state[5] != 0;
}
