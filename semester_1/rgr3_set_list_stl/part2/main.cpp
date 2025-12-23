#include <iostream>
#include <list>
#include <string>
#include <fstream>

struct Author {
    std::string last_name;
    std::string first_name;
    std::string patronymic;
};

struct Book {
    int udc;
    std::list<Author> authors;
    std::string title;
    int year;
};

void PrintAuthor(const Author& a) {
    std::cout << a.last_name << " " << a.first_name << " " << a.patronymic;
}

void PrintBook(const Book& b) {
    std::cout << "UDC: " << b.udc
              << " | \"" << b.title << "\" (" << b.year << ")\n";
    std::cout << "  Authors:\n";
    for (std::list<Author>::const_iterator it = b.authors.begin();
         it != b.authors.end(); ++it) {
        std::cout << "    ";
        PrintAuthor(*it);
        std::cout << "\n";
    }
}

void LoadBooksFromFile(const std::string& filename, std::list<Book>& books) {
    std::ifstream in(filename.c_str());
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }

    books.clear();

    while (true) {
        Book b;
        int authors_count;

        if (!(in >> b.udc)) {
            break;
        }
        in.ignore(1);

        std::getline(in, b.title);
        if (!(in >> b.year)) {
            break;
        }
        if (!(in >> authors_count)) {
            break;
        }

        b.authors.clear();
        for (int i = 0; i < authors_count; ++i) {
            Author a;
            if (!(in >> a.last_name >> a.first_name >> a.patronymic)) {
                break;
            }
            b.authors.push_back(a);
        }

        std::list<Book>::iterator it = books.begin();
        while (it != books.end() && it->title < b.title) {
            ++it;
        }
        books.insert(it, b);
    }
}

void AddBook(std::list<Book>& books, const Book& b) {
    std::list<Book>::iterator it = books.begin();
    while (it != books.end() && it->title < b.title) {
        ++it;
    }
    books.insert(it, b);
}

void RemoveBookByTitle(std::list<Book>& books, const std::string& title) {
    for (std::list<Book>::iterator it = books.begin();
         it != books.end(); ) {
        if (it->title == title) {
            it = books.erase(it);
        } else {
            ++it;
        }
    }
}

void FindBooksByTitle(const std::list<Book>& books,
                      const std::string& title) {
    std::cout << "Books with title \"" << title << "\":\n";
    for (std::list<Book>::const_iterator it = books.begin();
         it != books.end(); ++it) {
        if (it->title == title) {
            PrintBook(*it);
        }
    }
}

bool AuthorEquals(const Author& a,
                  const std::string& last,
                  const std::string& first,
                  const std::string& pat) {
    return a.last_name == last &&
           a.first_name == first &&
           a.patronymic == pat;
}

void FindBooksByAuthor(const std::list<Book>& books,
                       const std::string& last,
                       const std::string& first,
                       const std::string& pat) {
    std::cout << "Books by author "
              << last << " " << first << " " << pat << ":\n";

    for (std::list<Book>::const_iterator it = books.begin();
         it != books.end(); ++it) {
        bool has_author = false;
        for (std::list<Author>::const_iterator ait = it->authors.begin();
             ait != it->authors.end(); ++ait) {
            if (AuthorEquals(*ait, last, first, pat)) {
                has_author = true;
                break;
            }
        }
        if (has_author) {
            PrintBook(*it);
        }
    }
}

void AddAuthorToBook(std::list<Book>& books,
                     const std::string& title,
                     const Author& author) {
    for (std::list<Book>::iterator it = books.begin();
         it != books.end(); ++it) {
        if (it->title == title) {
            std::list<Author>::iterator ait = it->authors.begin();
            while (ait != it->authors.end() &&
                   ait->last_name < author.last_name) {
                ++ait;
            }
            it->authors.insert(ait, author);
        }
    }
}

void RemoveAuthorFromBook(std::list<Book>& books,
                          const std::string& title,
                          const std::string& last,
                          const std::string& first,
                          const std::string& pat) {
    for (std::list<Book>::iterator it = books.begin();
         it != books.end(); ++it) {
        if (it->title == title) {
            for (std::list<Author>::iterator ait = it->authors.begin();
                 ait != it->authors.end(); ) {
                if (AuthorEquals(*ait, last, first, pat)) {
                    ait = it->authors.erase(ait);
                } else {
                    ++ait;
                }
            }
        }
    }
}

int main() {
    std::list<Book> books;

    LoadBooksFromFile("books.txt", books);

    std::cout << "All books (sorted by title):\n";
    for (std::list<Book>::const_iterator it = books.begin();
         it != books.end(); ++it) {
        PrintBook(*it);
    }

    std::string title = "WarAndPeace";
    FindBooksByTitle(books, title);

    std::string last = "Tolstoy";
    std::string first = "Leo";
    std::string pat = "-";
    FindBooksByAuthor(books, last, first, pat);

    Author new_author;
    new_author.last_name = "NewAuthor";
    new_author.first_name = "Name";
    new_author.patronymic = "-";
    AddAuthorToBook(books, title, new_author);

    RemoveAuthorFromBook(books, title, "NewAuthor", "Name", "-");

    Book new_book;
    new_book.udc = 123;
    new_book.title = "ExampleBook";
    new_book.year = 2024;
    new_book.authors.clear();
    Author ex_a;
    ex_a.last_name = "Ivanov";
    ex_a.first_name = "Ivan";
    ex_a.patronymic = "Ivanovich";
    new_book.authors.push_back(ex_a);
    AddBook(books, new_book);

    RemoveBookByTitle(books, "ExampleBook");

    return 0;
}
