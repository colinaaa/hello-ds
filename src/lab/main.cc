#include <iostream>
#include <vector>

#include "2/List.hh"
#include "List.hh"
void print_menu(void) {
  /*
   * Function Name: print_menu
   * Module: Main control
   * Parameter: None
   * Return: None
   * Use: print the menu
   */

  std::cout << R"table(
      +--------------------------------------------------------------------+
      |                Welcome to link list demo system!                   |
      |               Here are some functions you can call:                |
      |                                                                    |
      |               1: init_list           2: destroy_list               |
      |               3: clear_list          4: is_list_empty              |
      |               5: list_length         6: get_list_item              |
      |               7: locate_list_item    8: piror_list_item            |
      |               9: next_list_item     10: list_insert                |
      |              11: list_delete        12: print_list                 |
      |                             0: quit                                |
      |                                                                    |
      |Enter the number of the function and see the usage and call it!     |
      |Enter 0 to quit the demo system.                                    |
      +--------------------------------------------------------------------+
      )table";
}

int main() {
  // a variable to save the function choose
  int function_choose = 0xff;

  while (function_choose != 0) {
    // print the menu
    print_menu();
    scanf("%d", &function_choose);

    // some variable to save the parameters
    int id = 0;
    int elem = 0;
    int index = 0;
    int out = 0;
    const auto n = 10;
    std::vector<Lab2::List<int>> lists(n);
    try {
      switch (function_choose) {
        case 1: {
          printf("/*\n");
          printf(" * Function Name: init_list\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list *L\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: initial the link list\n");
          printf(" */\n");
          printf("\n");
          printf("Then, enter the list id: ");
          std::cin >> id;
          if (id >= n) {
            printf("Init error\n");
          } else {
            lists[id] = Lab2::List<int>();
          }

        } break;

        case 2: {
          printf("/*\n");
          printf(" * Function Name: destroy_list\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list *L\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: destroy the link list\n");
          printf(" */\n");
          printf("\n");
          printf("Then, enter the list id: ");
          std::cin >> id;

          break;
        }

        case 3: {
          printf("/*\n");
          printf(" * Function Name: clear_list\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list *L\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: let the link list empty\n");
          printf(" */\n");
          printf("\n");
          printf("Then, enter the list id: ");
          std::cin >> id;
          lists[id].clear();

          printf("\n");
          break;
        }

        case 4: {
          printf("/*\n");
          printf(" * Function Name: is_list_empty\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list L\n");
          printf(" * Return: int(true or false)\n");
          printf(" * Use: judge if the link list is empty\n");
          printf(" */\n");
          printf("\n");
          printf("Then, enter the list id: ");

          std::cin >> id;
          auto em = lists[id].empty();
          std::cout << (em ? "Yes" : "NO") << std::endl;
          break;
        }
        case 5:
          printf("/*\n");
          printf(" * Function Name: list_length\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list L\n");
          printf(" * Return: int(the length)\n");
          printf(" * Use: get the length of link list\n");
          printf(" */\n");
          printf("\n");
          printf("Then, enter the list id: ");
          std::cin >> id;
          std::cout << lists[id].length();
          break;

        case 6:
          printf("/*\n");
          printf(" * Function Name: get_list_item\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list L, int order, int *elem\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: get the ordered element of link list\n");
          printf(" */\n");
          printf("\n");
          printf("                           Format: id index\n");
          printf("Then, enter the list id and index: ");

          std::cin >> id >> out;
          std::cout << lists[id].get(out);
          printf("\n");
          break;

        case 7:
          printf("/*\n");
          printf(" * Function Name: locate_list_item\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list L, int ordered_elem\n");
          printf(" * Return: int(index)\n");
          printf(" * Use: get the index of ordered item\n");
          printf(" */\n");
          printf("\n");
          printf("                             Format: id element\n");
          printf("Then, enter the list id and element: ");

          std::cin >> id >> elem;
          std::cout << lists[id].locate(elem, [](const int &a, const int &b) { return a == b; });
          printf("\n");
          break;

        case 8:
          printf("/*\n");
          printf(" * Function Name: piror_list_item\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list L, int elem, int *elem_pre\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: get the ordered element's piror\n");
          printf(" */\n");
          printf("\n");
          printf("                             Format: id element\n");
          printf("Then, enter the list id and element: ");
          std::cin >> id >> elem;
          std::cout << lists[id].prior(elem);
          printf("\n");
          break;

        case 9:
          printf("/*\n");
          printf(" * Function Name: next_list_item\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list L, int elem, int *elem_next\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: get the ordered element's next\n");
          printf(" */\n");
          printf("\n");
          printf("                             Format: id element\n");
          printf("Then, enter the list id and element: ");

          std::cin >> id >> elem;
          std::cout << lists[id].next(elem);
          printf("\n");
          break;

        case 10:
          printf("/*\n");
          printf(" * Function Name: list_insert\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list *L, int order, int elem\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: insert a element in the link list\n");
          printf(" */\n");
          printf("\n");
          printf("                                    Format: id index element\n");
          printf("Then, enter the list id, index and element: ");
          lists[id].insert(index, elem);
          printf("\n");
          break;

        case 11:
          printf("/*\n");
          printf(" * Function Name: list_delete\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list *L, int order, int *elem\n");
          printf(" * Return: int(status)\n");
          printf(" * Use: delete a element in the link list\n");
          printf(" */\n");
          printf("\n");
          printf("                           Format: id index\n");
          printf("Then, enter the list id and index: ");

          lists[id].remove(index);
          printf("\n");
          break;

        case 12:
          printf("/*\n");
          printf(" * Function Name: print_list\n");
          printf(" * Module: Data structures\n");
          printf(" * Parameter: link_list L, char *payload\n");
          printf(" * Return: None\n");
          printf(" * Use: print the elements of the linklist to the payload\n");
          printf(" */\n");
          printf("\n");
          printf("Then, enter the list id: ");
          lists[id].traverse([](int &x) { std::cout << x; });
          printf("\n");
          break;

        case 0:
          printf("Thanks for using my demo system!\n");
          break;

        default:
          printf("You entered the wrong num, please re-enter the num.\n");
          printf("\n");
          break;
      }
    } catch (std::overflow_error &e) {
      std::cout << e.what() << std::endl;
    } catch (std::underflow_error &e) {
      std::cout << e.what() << std::endl;
    } catch (std::runtime_error &e) {
      std::cout << e.what() << std::endl;
    }
  }

  return 0;
}
