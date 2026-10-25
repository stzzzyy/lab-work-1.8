#include <iostream>
#include <iomanip>

const int SIGN_BIT_POS   = 31;
const int HIGH_DATA_BIT  = 30;
const int TEST_DATA_SIZE = 3;


// Частина 1: Демонстрація структурних операторів C++

void demonstrateControlStructures()
{
    std::cout << "\n               PART-1 (Demonstration of control structures)\n\n";

    int nDemoA = 10;
    int nDemoB = 20;

    // 1. Оператор вибору (умовна форма if)
    std::cout << "(1) Conditional statement (if):\n";
    if (nDemoA != nDemoB)
    {
        std::cout << "\n    nDemoA (" << nDemoA << ") is not equal to nDemoB (" << nDemoB << ")\n\n";
    }

    // 2. Оператор вибору (альтернативна форма if-else)
    std::cout << "(2) Alternative statement (if-else):\n";
    if (nDemoA == nDemoB)
    {
        std::cout << "\n    Values are equal.\n\n";
    }
    else
    {
        std::cout << "\n    Values are different.\n\n";
    }

    // 3. Оператор вибору (перемикач switch-case)
    std::cout << "(3) Selection statement (switch-case):\n";
    int nChoice = 2;
    switch (nChoice)
    {
        case 1:
            std::cout << "\n    Option 1 selected\n";
            break;
        case 2:
            std::cout << "\n    Option 2 selected (matched value)\n";
            break;
        default:
            std::cout << "\n    Default branch executed\n";
            break;
    }
    std::cout << "\n";

    // 4. Оператор повторення з передумовою (while-do)
    std::cout << "(4) Pre-test loop (while-do):\n    ";
    int nCounterWhile = 1;
    while (nCounterWhile <= 3)
    {
        std::cout << nCounterWhile << " ";
        nCounterWhile++;
    }
    std::cout << "\n    (done)\n\n";

    // 5. Оператор повторення з післяумовою (do-while)
    std::cout << "(5) Post-test loop (do-while):\n    ";
    int nCounterDo = 1;
    do
    {
        std::cout << nCounterDo << " ";
        nCounterDo++;
    } while (nCounterDo <= 3);
    std::cout << "\n    (done)\n\n";

    // 6. Оператор повторення з параметром (for)
    std::cout << "(6) Loop with counter (for):\n    ";
    for (int nIndex = 1; nIndex <= 3; nIndex++)
    {
        std::cout << nIndex << " ";
    }
    std::cout << "\n    (done)\n\n";
}


// Частина 2: Бітове моделювання операцій (Варіант 3, Таблиця 16)


// Моделювання операції відношення '<' без використання оператора '<'
bool bitwiseLessThan(int nA, int nB)
{
    // Отримуються знакові (31-і) біти: 1 для від'ємних, 0 для додатних
    int nSignA = (nA >> SIGN_BIT_POS) & 1;
    int nSignB = (nB >> SIGN_BIT_POS) & 1;

    // Якщо знаки чисел різні
    if (nSignA != nSignB)
    {
        // Від'ємне число завжди менше за додатне
        return nSignA == 1;
    }

    // Якщо знаки однакові, скануються біти від 30-го до 0-го за допомогою маски
    unsigned int unMask = 1u << HIGH_DATA_BIT;

    while (unMask != 0)
    {
        int nBitA = ((unsigned int)nA & unMask) != 0 ? 1 : 0;
        int nBitB = ((unsigned int)nB & unMask) != 0 ? 1 : 0;

        if (nBitA != nBitB)
        {
            // Число, у якого поточний біт дорівнює 0, є меншим
            return nBitA == 0;
        }

        unMask >>= 1;
    }

    // Якщо всі біти однакові — числа рівні, тому nA < nB дає false
    return false;
}

// Моделювання операції додавання '+' без використання оператора '+'
int bitwiseAdd(int nA, int nB)
{
    // Апаратний двійковий суматор з поширенням переносу
    while (nB != 0)
    {
        // 1. Біти переносу виникають там, де в обох числах стоять одиниці
        unsigned int unCarry = (unsigned int)(nA & nB);

        // 2. Додавання бітів без урахування переносу (XOR)
        nA = nA ^ nB;

        // 3. Зсув переносу в наступний старший розряд
        nB = (int)(unCarry << 1);
    }

    return nA;
}

int main()
{
    demonstrateControlStructures();

    std::cout << "\n               PART-2 (Bitwise simulation [Variant-3, Table-16])\n\n";


    // Тестування операції відношення '<'
    // Контрольні пари за Таблицею 16: (84, 83), (63, 127), (-77, -77)

    int arrLessA[TEST_DATA_SIZE] = {84, 63, -77};
    int arrLessB[TEST_DATA_SIZE] = {83, 127, -77};

    std::cout << "               1. Testing relational operator '<' simulation\n\n";
    std::cout << "--------------------------------------------------------------------------\n";
    std::cout << std::left
              << std::setw(12) << "Operand 1"
              << std::setw(12) << "Operand 2"
              << std::setw(20) << "Bitwise Result"
              << std::setw(20) << "Expected (<)"
              << std::setw(10) << "Status"
              << "\n";
    std::cout << "--------------------------------------------------------------------------\n";

    for (int nIdx = 0; nIdx < TEST_DATA_SIZE; nIdx++)
    {
        int  nOp1         = arrLessA[nIdx];
        int  nOp2         = arrLessB[nIdx];
        bool bCustomRes   = bitwiseLessThan(nOp1, nOp2);
        bool bStandardRes = (nOp1 < nOp2);

        std::cout << std::left
                  << std::setw(12) << nOp1
                  << std::setw(12) << nOp2
                  << std::setw(20) << (bCustomRes ? "true (1)" : "false (0)")
                  << std::setw(20) << (bStandardRes ? "true (1)" : "false (0)")
                  << std::setw(10) << (bCustomRes == bStandardRes ? "[CORRECT]" : "[ERROR]")
                  << "\n";
        std::cout << "--------------------------------------------------------------------------\n";
    }

    std::cout << "\n";

    // Тестування операції додавання '+'
    // Контрольні пари за Таблицею 16: (-10, 12), (31, 32), (15, 41)

    int arrAddA[TEST_DATA_SIZE] = {-10, 31, 15};
    int arrAddB[TEST_DATA_SIZE] = {12, 32, 41};

    std::cout << "               2. Testing addition operator '+' simulation\n\n";
    std::cout << "--------------------------------------------------------------------------\n";
    std::cout << std::left
              << std::setw(12) << "Operand 1"
              << std::setw(12) << "Operand 2"
              << std::setw(20) << "Bitwise Result"
              << std::setw(20) << "Expected (+)"
              << std::setw(10) << "Status"
              << "\n";
    std::cout << "--------------------------------------------------------------------------\n";

    for (int nIdx = 0; nIdx < TEST_DATA_SIZE; nIdx++)
    {
        int nOp1         = arrAddA[nIdx];
        int nOp2         = arrAddB[nIdx];
        int nCustomRes   = bitwiseAdd(nOp1, nOp2);
        int nStandardRes = nOp1 + nOp2;

        std::cout << std::left
                  << std::setw(12) << nOp1
                  << std::setw(12) << nOp2
                  << std::setw(20) << nCustomRes
                  << std::setw(20) << nStandardRes
                  << std::setw(10) << (nCustomRes == nStandardRes ? "[CORRECT]" : "[ERROR]")
                  << "\n";
        std::cout << "--------------------------------------------------------------------------\n";
    }

    std::cout << "\nExecution completed successfully.\n";
    return 0;
}