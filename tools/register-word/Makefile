CC = clang
LIBS=/usr/lib/sqlite3
INC=-Iinclude
DEST = bin
SRC_DIR = src
register_words: $(SRC)
	@mkdir -p $(DEST)
	$(CC) $(SRC_DIR)/register_words.c -o $(DEST)/register_words $(INC) -lsqlite3 -L/usr/lib/

.PHONY: clean run
run: register_words
	$(DEST)/register_words

insert:
	clang $(SRC_DIR)/insert.c $(SRC_DIR)/connect.c -o $(DEST)/insert_words $(INC) -lsqlite3 -L/usr/lib/
	./$(DEST)/insert_words

create:
	clang $(SRC_DIR)/create.c $(SRC_DIR)/connect.c -o $(DEST)/create $(INC) -lsqlite3 -L/usr/lib/
	./$(DEST)/create

clean:
	rm -f $(DEST)/*
