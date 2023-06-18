
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
typedef struct {
  char name[20];
  char password[20];
  int accountValue;
  int logedIn;
} account;

account accountList[100] = {0};

void clear() { system("clear"); }
void printLoginMenu() {
  clear();
  printf("###########BANKING ACCOUNTS###############\n");
  printf("\t1. CREATE NEW ACCOUNT\n");
  printf("\t2. LOGE IN\n");
  printf("\t3. QUIT\n");
  printf(" => ");
}
account *newAccount() {
  char name[20] = {0};
  char password[20] = {0};
  printf("\tName: ");
  scanf("%s", name);
  for (int i = 0; i < 100; i++) {
    if (name == accountList[i].name) {
      return NULL;
    }
  }
  printf("\tPassword: ");
  scanf("%s", password);
  account new = {0};

  strcpy(new.name, name);
  strcpy(new.password, password);
  new.accountValue = 500;
  new.logedIn = 0;
  for (int i = 0; i < 100; i++) {
    if (accountList[i].name[0] == '\0') {
      printf("account added\n");
      accountList[i] = new;
      printf("%s\n", accountList[i].name);
      return &accountList[i];
    }
  }
  return NULL;
}
int sendMoney(account *acc) {
  char buffer[64];
  printf("Name To Send Money To\n => ");
  scanf("%s", buffer);
  account *dest;
  int found = 0;
  for (int i = 0; i < 100; i++) {
    if (strcmp(accountList[i].name, buffer) == 0) {
      found = 1;
      dest = &accountList[i];
    }
  }
  if (!found) {
    return 1;
  }
  unsigned int value = 0;
  printf("How Much Money do U want to send \n => ");
  scanf("%ud", &value);
  if (value > acc->accountValue) {
    printf("U dont have that much Money\n");
    return 1;
  }
  acc->accountValue -= value;
  dest->accountValue += value;
  return 0;
}
void printAll() {
  clear();
  printf("##############\n");
  for (int i = 0; i < 100; i++) {
    if (accountList[i].name[0] != '\0') {
      printf("%d\t%s\n", i + 1, accountList[i].name);
    }
  }
}
void showMoney(account *acc) { printf("U Got %d$\n", acc->accountValue); }
void AccountMenu(account *acc) {
  clear();
  printf("LOGGED IN AS: \t %s \n", acc->name);
  char buffer[64];
  while (acc->logedIn) {
    printf("\t1. Send\n");
    printf("\t2. See Money\n");
    printf("\t3. See All Accounts\n");
    printf("\t4. Log Out\n");
    printf(" => ");
    scanf("%s", buffer);

    if (buffer[0] == '1') {
      sendMoney(acc);
    }
    if (buffer[0] == '2') {
      showMoney(acc);
    }
    if (buffer[0] == '3') {
      printAll();
    }
    if (buffer[0] == '4') {
      printf("Logging Out\n");
      acc->logedIn = 0;
      return;
    }
  }
}

account *login(account *acc) {
  clear();
  printf("#######Login#######\n");
  char name[20] = {0};
  printf("\tNAME:");
  scanf("%s", name);
  int found = 0;
  for (int i = 0; i < 100; i++) {
    if (strcmp(accountList[i].name, name) == 0) {
      acc = &accountList[i];
      found = 1;
      break;
    }
  }

  if (!found) {
    return NULL;
  }
  char password[20] = {0};
  printf("\tPASSWORD: ");
  scanf("%s", password);

  if (strcmp(acc->password, password) == 0) {
    printf("SUCCESFULLY LOGGED IN \n");
    acc->logedIn = 1;
  }

  return acc;
}
int main(void) {
  account *myAccount = {0};
  char buffer[64] = {0};
  while (1) {
    printAll();
    if (myAccount != NULL && myAccount->logedIn) {
      AccountMenu(myAccount);

    } else {
      printLoginMenu();
      memset(buffer, 0, sizeof(buffer));
      scanf("%s", buffer);

      if (buffer[0] == '1') {
        myAccount = newAccount();
        if (myAccount == NULL) {
          printf("Something went wrong\n");
        }

      } else if (buffer[0] == '2') {
        myAccount = login(myAccount);
      } else if (buffer[0] == '3') {
      }
    }
  }
}
