#pragma once
#include "Head.h"


//координаты, заполняем вектор точек, в которые можем прийти, потом перебором подбираем номера

double field_cell_size = 20;

void king_solve(vector<point> &Field);
void knight_solve(vector<point> &Field);

void draw_king(point a) {
	glRasterPos2i(a.x - 5, a.y - 7);
	glColor3f(0, 1, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'K');
}

void draw_knight(point a) {
	glRasterPos2i(a.x - 5, a.y - 7);
	glColor3f(0, 1, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'K');
}

void draw_num(point a, int n){  //костыли? не думаю.
	if (n < 10) {
		glRasterPos2i(a.x - 3, a.y - 5);
		glColor3f(1, 0, 0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + n);
	}
	else if (n < 100) {
		int i = n / 10;
		n = n % 10;
		glRasterPos2i(a.x-7, a.y-5);
		glColor3f(1, 0, 0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, char(i+48));
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + n%10);
	}
	else if (n < 1000) {
		int i = n / 100;
		n = n % 100;
		int t = n / 10;
		n = n % 10;
		glRasterPos2i(a.x - 11, a.y - 5);
		glColor3f(1, 0, 0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, char(i + 48));
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, char(t + 48));
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + n % 10);
	}
}

void draw_cell(point a) {
	
	glPointSize(10);
	glBegin(GL_LINE_LOOP);
	glVertex2d(a.x - field_cell_size / 2, a.y+field_cell_size/2);
	glVertex2d(a.x + field_cell_size / 2, a.y+field_cell_size/2);
	glVertex2d(a.x + field_cell_size / 2, a.y-field_cell_size/2);
	glVertex2d(a.x - field_cell_size / 2, a.y - field_cell_size / 2);
	glEnd();
}

int Field_size = 0;

void solve5() {
	display();
	int n;
	cin >> n;
	Field_size = (1 + (n - 1)) * (n - 1);  //нереально важные устанвоки для работы всего задания, без них кина не будет
	Field_size += n;
	field_cell_size = H / ((n - 1) * 2 + 1);
	vector<point> Field(Field_size);
	Field[0].x = 0;
	Field[0].y = (H / 2) - field_cell_size / 2;
	bool good = 1;
	glColor3f(1, 0, 0);
	int cnt = 0, prev_cnt = 1;
	draw_cell(Field[0]);
	draw_num(Field[0], 0);
	for (int i = 1; i < Field_size; i++) {   //Рисование поля(ебейший говнокод, мб когда-нибудь я сделаю тут красоту, но пока не сильно хочется)
		if (cnt > 0) {
			Field[i].y = Field[i - 1].y;
			Field[i].x = Field[i - 1].x + field_cell_size;
		}
		else {
			Field[i].y = Field[i - 1].y - field_cell_size;
			if (good) Field[i].x = -Field[i - 1].x - field_cell_size / 2;
			else Field[i].x = -Field[i - 1].x + field_cell_size / 2;
			cnt = prev_cnt + 1;
			if (prev_cnt == n - 1) good = 0;
			if (good) prev_cnt++;
			else prev_cnt--;
		}
		cnt--;
		draw_cell(Field[i]);
		draw_num(Field[i], i);
	}
	glFlush();

	//king_solve(Field);
	knight_solve(Field);

	glutSwapBuffers();
	glFlush();
}
void king_solve(vector<point> &Field){  //оно не совсем работает как надо, а то что работает не должно работать, но оно работает потому что полтора литра светлого нефильтрованного так решили
	int king_pos;
	point king_posit;
	cin >> king_pos;
	if (king_pos > Field_size || king_pos < 0) {
		bool checking = 0;
		while (!checking) {
			cin >> king_pos;
			if (king_pos < Field_size && king_pos > 0) checking = 1;
		}
	}

	king_posit.x = Field[king_pos].x; //нереально важные установки перед поиском всех клеток на 2 хода
	king_posit.y = Field[king_pos].y;
	draw_king(king_posit);
	vector<point> Kings_moves(19);
	Kings_moves[0].x = king_posit.x - field_cell_size;
	Kings_moves[0].y = king_posit.y + 2*field_cell_size;
	int cnt = 2, prev_cnt = 3;
	bool good = 1;
	glColor3f(0, 1, 0);

	for (int i = 1; i < 19; i++){ //Нахождение и рисование всех ходов короля
		if (cnt > 0) {
			Kings_moves[i].y = Kings_moves[i - 1].y;
			Kings_moves[i].x = Kings_moves[i - 1].x+field_cell_size;
		}
		else {
			Kings_moves[i].y = Kings_moves[i - 1].y - field_cell_size;
			if (good) Kings_moves[i].x = (Kings_moves[i - 1].x-(prev_cnt-1)*field_cell_size) - field_cell_size / 2;
			else Kings_moves[i].x = (Kings_moves[i - 1].x - (prev_cnt+1) * field_cell_size) + field_cell_size / 2;
			cnt = prev_cnt+1;
			if (prev_cnt == 4) good = 0;
			if (good) prev_cnt++;
			else prev_cnt--;
		}
		cnt--;
	}

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < Field_size; j++) {
			if (Kings_moves[i].x == Field[j].x && Kings_moves[i].y == Field[j].y) {
				draw_cell(Kings_moves[i]);
			}
		}
	}

	int king_to_go; 
	cin >> king_to_go;
	if (king_to_go > Field_size || king_to_go < 0) {
		bool checking2 = 0;
		while (!checking2) {
			cin >> king_to_go;
			if (king_to_go < Field_size && king_to_go > 0) checking2 = 1;
		}
	}

	point point_to_go; //нереально важные установки перед поиском пути, они костыльные, но рабочие
	point_to_go.x = Field[king_to_go].x;
	point_to_go.y = Field[king_to_go].y;
	vector<point> king_point_moves;
	point Curr;
	Curr.x = Field[king_pos].x;
	Curr.y = Field[king_pos].y;
	king_point_moves.push_back(Curr);
	bool x_move = 1;

	while (abs(Curr.x - point_to_go.x)>0 || abs(Curr.y - point_to_go.y) >0) {  //костыльный но рабочий алгос поиска наименьшего пути
		if (abs(Curr.x - point_to_go.x) >0 && abs(Curr.y - point_to_go.y) >0) {
			if (Curr.x > point_to_go.x) {
				if (Curr.y > point_to_go.y) {
					Curr.x -= field_cell_size/2;
					Curr.y -= field_cell_size;
					king_point_moves.push_back(Curr);
				}
				else {
					Curr.x -= field_cell_size / 2;
					Curr.y += field_cell_size;
					king_point_moves.push_back(Curr);
				}
			}
			else {
				if (Curr.y > point_to_go.y) {
					Curr.x += field_cell_size / 2;
					Curr.y -= field_cell_size;
					king_point_moves.push_back(Curr);
				}
				else {
					Curr.x += field_cell_size / 2;
					Curr.y += field_cell_size;
					king_point_moves.push_back(Curr);
				}
			}
		}
		else if (abs(Curr.x - point_to_go.x) > 0) {
			if (Curr.x > point_to_go.x) {
				Curr.x -= field_cell_size;
				king_point_moves.push_back(Curr);
			}
			else {
				Curr.x += field_cell_size;
				king_point_moves.push_back(Curr);
			}
		}
		else if (abs(Curr.y - point_to_go.y) > 0) {
			if (Curr.y > point_to_go.y) {
				Curr.y -= field_cell_size;
				if (x_move) {
					Curr.x -= field_cell_size / 2;
					x_move = !x_move;
				}
				else {
					Curr.x += field_cell_size / 2;
					x_move = !x_move;
				}
				king_point_moves.push_back(Curr);
			}
			else {
				Curr.y += field_cell_size;
				if (x_move) {
					Curr.x += field_cell_size / 2;
					x_move = !x_move;
				}
				else {
					Curr.x -= field_cell_size / 2;
					x_move = !x_move;
				}
				king_point_moves.push_back(Curr);
			}
		}
	}
	for (int i = 0; i < king_point_moves.size(); i++) {
		glColor3f(0, 0, 1);
		draw_cell(king_point_moves[i]);
	}
	glutSwapBuffers();
	glFlush();
}

void knight_moves_point(vector<point> &knight_move, point position, int k) { //тупа перебираем все варианты
	point move;
	move.x = position.x - field_cell_size * 2.5;
	move.y = position.y + field_cell_size;
	knight_move.push_back(move);
	move.x = position.x - field_cell_size * 2;
	move.y = position.y + field_cell_size*2;
	knight_move.push_back(move);
	move.x = position.x - field_cell_size * 0.5;
	move.y = position.y + field_cell_size*3;
	knight_move.push_back(move);
	move.x = position.x + field_cell_size *0.5;
	move.y = position.y + field_cell_size*3;
	knight_move.push_back(move);
	move.x = position.x + field_cell_size * 2;
	move.y = position.y + field_cell_size*2;
	knight_move.push_back(move);
	move.x = position.x + field_cell_size * 2.5;
	move.y = position.y + field_cell_size;
	knight_move.push_back(move);
	for (int i = k*12; i < k*12+6; i++) {
		move.x = knight_move[i].x;
		move.y = knight_move[i].y  - (knight_move[i].y-position.y)*2;
		knight_move.push_back(move);
	}
}


void knight_solve(vector<point> &Field) {  //неведомая ебаная хуета часть 2.
	int knight_posit;
	cin >> knight_posit;
	point knight_pos;
	knight_pos.x = Field[knight_posit].x;
	knight_pos.y = Field[knight_posit].y;
	draw_knight(knight_pos);
	vector<point> knight_first_move;
	knight_moves_point(knight_first_move, knight_pos, 0); //получаем все точки куда можем прийти за 1 ход
	vector<point> knight_second_move;
	
	for (int i = 0; i < 12; i++) {
		knight_moves_point(knight_second_move, knight_first_move[i], i); //для каждой точки с 1 хода перебираем все возможные ходы
	}
	glColor3f(0, 1, 0);
	for (int i = 0; i < knight_second_move.size(); i++) { //рисуем те точки которые в поле попадают
		for (int j = 0; j < Field_size; j++) {
			if (knight_second_move[i].x == Field[j].x && knight_second_move[i].y == Field[j].y) {
				draw_cell(knight_second_move[i]);
			}
		}
	}


	int point_to_go;
	cin >> point_to_go;
	point to_go;
	to_go.x = Field[point_to_go].x;
	to_go.y = Field[point_to_go].y;

	vector<point> moves, new_move;
	knight_moves_point(new_move, knight_pos, 0);
	double diff = 10;
	point position = knight_pos, pos_prev = knight_pos;
	/*Тут была идея перебора минимальный расстояний. То есть для каждой точки мы будем проверять расстояние до
	необходимой, и в точку с меньшим расстоянием двигаться, а потом для нее повторить этот цикл.
	но видать не судьба и ничего не работает*/
	while (diff > 0) {
		for (int i = 0; i < 12; i++) {
			if (sqrt(distance_point(new_move[i], to_go)) < diff) {
				diff = sqrt(distance_point(new_move[i], to_go));
				position = new_move[i];
			}
		}
		moves.push_back(position);
		new_move.clear();
		knight_moves_point(new_move, position, 0);
		cout << diff << '\n';
	}
	for (int i = 0; i < moves.size(); i++) {
		glColor3f(0, 0, 1);
		draw_cell(moves[i]);
	}
}

void problem_5(int argc, char**& argv) {
	scale = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(W, H);
	glutCreateWindow("Problem 5");
	glutDisplayFunc(solve5);
	//glutKeyboardFunc(keyboard_5);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}
