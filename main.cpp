#include "includes.h"
#include "caminho.h"

int main(){

	// declara��o de vari�veis
	int largura = 960; // largura da tela
	int altura = 540; // altura da tela
	bool acabou = false; // vari�vel que controla o loop do jogo
	int numCaminhos = 4; // n�mero de caminhos
	int fps = 60;
	int numCaracois = 100;
	int tempoSpawn = 120;
	int contador = 120;
	int seletor = 0;

	// declara��o de vari�veis da allegro
	ALLEGRO_DISPLAY *tela = NULL;
	ALLEGRO_EVENT_QUEUE *filaEventos = NULL;
	ALLEGRO_TIMER *timer = NULL;

	// cria��o dos 4 caminhos
	Caminho *caminho[numCaminhos];
	caminho[0] = new Caminho(0, 0, largura, 108);
	caminho[1] = new Caminho(0, 108, largura, 216);
	caminho[2] = new Caminho(0, 216, largura, 324);
	caminho[3] = new Caminho(0, 324, largura, 432);

	srand(time(NULL)); // gera uma seed baseada na hora atual para gerar n�meros aleat�rios pela funcao rand() 

	al_init(); // inicializa a allegro
    al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	tela = al_create_display(largura, altura); //cria a janela
	
	timer = al_create_timer(1.0 / fps);
	
	filaEventos = al_create_event_queue(); // cria a fila de eventos
 
	// registra fontes de eventos na fila de eventos
	al_register_event_source(filaEventos, al_get_display_event_source(tela));
	al_register_event_source(filaEventos, al_get_keyboard_event_source());
	al_register_event_source(filaEventos, al_get_timer_event_source(timer));
	
	al_start_timer(timer); 
	
	// loop do jogo
	while(!acabou){
		ALLEGRO_EVENT evento; // cria vari�vel de evento
		al_wait_for_event(filaEventos, &evento); // espera por algum evento
		if(evento.type == ALLEGRO_EVENT_TIMER){
			contador--;
			if(contador == 0){
				caminho[aleatorio(0,3)]->adicionarCaracol();
				contador = aleatorio(0, tempoSpawn);
			}
			for(int i = 0; i < numCaminhos; i++){
				caminho[i]->atualizarCaracois();
				caminho[i]->atualizarComidas();
				caminho[i]->desenharCaracois();
				caminho[i]->desenharComidas();
			}
			caminho[seletor]->desenhar();
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ // evento disparado quando clicamos no X da tela
			acabou = true;
		}
		
		else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){ // evento disparado quando uma tecla � pressionada
			switch(evento.keyboard.keycode){ // verifica qual tecla foi pressionada
				case ALLEGRO_KEY_ESCAPE:
					acabou = true;
					break;
				case ALLEGRO_KEY_UP:
					seletor--;
					if(seletor < 0)
						seletor = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					seletor++;
					if(seletor > numCaminhos-1)
						seletor = numCaminhos-1;
					break;
				case ALLEGRO_KEY_LEFT:
					cout << seletor << endl;
					break;
				case ALLEGRO_KEY_RIGHT:
					caminho[3]->adicionarCaracol();
					break;
				case ALLEGRO_KEY_Q:
					caminho[seletor]->adicionarComida();
					break;
				
				
			}

		}

	}

	return 0;

}






