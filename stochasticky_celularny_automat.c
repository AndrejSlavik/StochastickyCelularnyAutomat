#define _CRT_SECURE_NO_WARNINGS
#define STATE_MAX_LEN 80
#define RULES_MAX_LEN 6
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int randomGen(int a, int b) {
	return rand() % (b - a + 1) + a;
}

void rulesArray(int rules[]) {
	int i, rule = 0;
	printf("Enter a number of rules: ");
	scanf("%d", &rule);
	while ((rule > RULES_MAX_LEN) || (rule % 2 != 0)) {
		printf("Wrong number of rules!\n\nEnter a number of rules: ");
		scanf("%d", &rule);
	}
	for (i = 0; i < rule; i++) {
		printf("Enter a probability for rule %d: ", i);
		scanf("%d", &rules[i]);
	}
	printf("\nState length: %d\n\n", STATE_MAX_LEN);
	printf("RULES:\n");
	for (i = 0; i < rule; i++) {
		printf("Rule [%d]: ... %d%%\n", i, rules[i]);
	}
}

void randomStart(int state[]) {
	int i = 0;
	for (i = 0; i < STATE_MAX_LEN; i++) {
		state[i] = randomGen(0, 1);
	}
}

void generateState(int state[], int rules[]) {
	int i, bit = 0, p = 0;
	for (i = 0; i < STATE_MAX_LEN; i++) {
		if (i == 0)
			p = state[0] + state[1] + state[2];
		else if (i == 1)
			p = state[0] + state[1] + state[2] + state[3];
		else if (i == (STATE_MAX_LEN - 2))
			p = state[i - 2] + state[i - 1] + state[i] + state[i + 1];
		else if (i == (STATE_MAX_LEN - 1))
			p = state[i - 2] + state[i - 1] + state[i];
		else 
			p = state[i - 2] + state[i - 1] + state[i] + state[i + 1] + state[i + 2];
		bit = randomGen(0, 100);
		if (bit <= (rules[p])) 
			bit = 1;
		else 
			bit = 0;
		state[i] = bit;
		if (state[i] == 1)
			printf("*");
		else
			printf(" ");
	}
}

void printState(int state[],int rules[],int iterations) {
	int i,j;
	for (i = 0; i < iterations; i++) {
		printf("\nt=%d ", i);
		if (i == 0) {
			randomStart(state);
			for (j = 0; j < STATE_MAX_LEN; j++) {
				state[j] = randomGen(0, 1);
				if (state[j] == 1)
					printf("*");
				else
					printf(" ");
			}
		}
		else {
			generateState(state, rules);
			Sleep(300);
		}
	}
}

void cellular_automaton() {
	int iterations = 0, state[STATE_MAX_LEN], rules[RULES_MAX_LEN];
	printf("\n\t[STOCHASTIC CELLULAR AUTOMATON]\n\n................................................\n\n");
	printf("Enter a number of iterations: ");
	scanf("%d", &iterations);
	rulesArray(rules);
	printf("\n\nPress enter to continue...");
	(void)getchar();
	(void)getchar();
	system("cls");
	printf("Evolution of the automaton:\n\n");
	printState(state, rules, iterations);
}

int main() {
	srand(time(0));
	cellular_automaton();
	return 0;
}