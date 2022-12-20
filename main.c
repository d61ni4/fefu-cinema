#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_length(char *login, char *password) {
  int check = true;
  
  int check_login = true;
  int login_length = strlen(login);
  if (login_length < 3 || login_length > 20) {
    printf("Некорректный логин. Логин должен содержать не менее 3 и не более 20 символов.\n");
    check_login = false;
  }

  int check_password = true;
  int password_length = strlen(password);
  if (password_length < 6 || password_length > 20) {
    printf("Некорректный пароль. Пароль должен содержать не менее 6 и не более 20 символов.\n");
    check_password = false;
  }
  if (check_login == true && check_password == true) {
    check = true;
  } else {check = false;}

  return check;
}

int check_card_number(char *card_number) {
  int check = true;
  char *numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  int card_number_length = strlen(card_number);
  
  int check_length = true;
  if (card_number_length != 16) {check_length = false;}

  int check_numbers = false;
  for (int i = 0; i < card_number_length; i++) {
    char card_number_char = card_number[i];
    for (int j = 0; j < 10; j++) {
      if (strchr(numbers[j], card_number_char)) {check_numbers = true;}
    }
  }

  if (check_length == true && check_numbers == true) {
    check = true;
  } else {printf("Некорректный номер карты. Номер карты должен содержать 16 цифр.\n");}
  
  return check;
}

int check_symbols(char *login, char *password) {
  int check = false;
  char *names[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
  char *NAMES[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
  char *numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

  int check_login = false;
  int login_length = strlen(login);
  int count_login = 0;
  for (int i = 0; i < login_length; i++) {
    char login_char = login[i];
    for (int j = 0; j < 26; j++) {
      if (strchr(names[j], login_char) != NULL) {count_login += 1;}
      if (strchr(NAMES[j], login_char) != NULL) {count_login += 1;}
    }
    for (int k = 0; k < 10; k++) {
      if (strchr(numbers[k], login_char) != NULL) {count_login += 1;}
    }
  }
  if (count_login == login_length) {check_login = true;}

  if (check_login == false) {printf("Некорректный логин. Логин должен состоять из символов латинского алфавита и цифр.\n");}

  int check_password = false;
  int count_password = 0;
  int password_length = strlen(password);
  int check_password_symbols = false;
  for (int i = 0; i < password_length; i++) {
    char password_char = password[i];
    for (int j = 0; j < 26; j++) {
      if (strchr(names[j], password_char) != NULL) {count_password += 1;}
      if (strchr(NAMES[j], password_char) != NULL) {count_password += 1;}
    }
    for (int k = 0; k < 10; k++) {
      if (strchr(numbers[k], password_char) != NULL) {count_password += 1;}
    }
  }
  if (count_password == password_length) {check_password_symbols = true;}

  int check_names = false;
  for (int i = 0; i < password_length; i++) {
    char password_char = password[i];
    for (int j = 0; j < 26; j++) {
      if (strchr(names[j], password_char)) {check_names = true;}
    }
  }

  int check_numbers = false;
  for (int i = 0; i < password_length; i++) {
    char password_char = password[i];
    for (int j = 0; j < 10; j++) {
      if (strchr(numbers[j], password_char)) {check_numbers = true;}
    }
  }

  int check_NAMES = false;
  for (int i = 0; i < password_length; i++) {
    char password_char = password[i];
    for (int j = 0; j < 26; j++) {
      if (strchr(NAMES[j], password_char)) {check_NAMES = true;}
    }
  }

  if (check_numbers == true && check_names == true && check_NAMES == true && check_password_symbols == true) {
    check_password = true;
  } else {printf("Некорректный пароль. Пароль должен состоять из символов латинского алфавита и цифр и содержать буквы верхнего, нижнего регистра и цифры.\n");}

  if (check_login == true && check_password == true) {check = true;}
  return check;
}

void registration(char *login, char *password, char* card_number) {
  if (check_length(login, password) == true && check_symbols(login, password) == true && check_card_number(card_number) == true) {
    printf("Успешная регистрация!\n");
    FILE *users;
    users = fopen("users.txt", "a");
    fputs(login, users);
    fputs("\n", users);
    fputs(password, users);
    fputs("\n", users);
    fputs(card_number, users);
    fputs("\n", users);
    fclose(users);
  }
}

void log_in(char *login, char *password, char* card_number) {
  if (check_length(login, password) == true && check_symbols(login, password) == true && check_card_number(card_number) == true) {
    FILE *users;
    ssize_t read;
    char *file_login = NULL;
    char *file_password = NULL;
    char* file_card_number = NULL;
    size_t len = 0;
    users = fopen("users.txt", "r");
    
    while (read != -1) {
      read = getline(&file_login, &len, users);
      if (read == -1) {
        printf("Такой пользователь не найден.\n");
        return;
        }
      read = getline(&file_password, &len, users);
      read = getline(&file_card_number, &len, users);
      if (strcmp(login, strtok(file_login, "\n")) == 0) {read = -1;}
    }
    
    if (strcmp(login, strtok(file_login, "\n")) == 0 && strcmp(password, strtok(file_password, "\n")) == 0 && strcmp(card_number, strtok(file_card_number, "\n")) == 0) {
      printf("Вход выполнен успешно.\n");
    } else {printf("Неправильный пароль и/или логин.\n");}
    fclose(users);
    
  }
}
