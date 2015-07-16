#include <c2d2\chien2d2.h>
#include <iostream>
#include "Math\Vector2D.h"
#include "Math\AffineTransform.h"

using namespace std;
using namespace math;


int nave;
int mouseTx;
int shield;
int shield2;

int naveSpeed = 5;

#define WD_SCREEN 1024
#define  HG_SCREEN 768



Vector2D navePos, mousePos, shieldPos, shieldPos1; //vetores de posicao

Vector2D naveDir; //vetores de direcao

Vector2D shieldOffSet, shieldOffSet2;

void setup()
{
	nave = C2D2_CarregaSpriteSet("Assets/nave.png", 0, 0);
	navePos = Vector2D(100, 200);
	mouseTx = C2D2_CarregaSpriteSet("Assets/mousetx.png", 0, 0);
	shield = C2D2_CarregaSpriteSet("Assets/shield.png", 0, 0);
	shield2 = C2D2_CarregaSpriteSet("Assets/sh2.png", 0, 0);

	shieldOffSet = Vector2D(80, 0);
	shieldOffSet2 = Vector2D(80, 0);


}


void update(float secs)
{
	C2D2_Mouse* mouse = C2D2_PegaMouse();

	mousePos = Vector2D(mouse->x, mouse->y);
	
	shieldOffSet = shieldOffSet.rotate(toRadians(120) * secs);

	shieldOffSet2 = shieldOffSet2.rotate(toRadians(-720) * secs);

	shieldPos = navePos + shieldOffSet;

	shieldPos1 = navePos + shieldOffSet2;

	if (mouse->botoes[0].pressionado)
	{
		naveDir = (mousePos - navePos).normalize() * naveSpeed;
		
	}

	navePos += naveDir;  

	if (navePos.x > WD_SCREEN || navePos.x < 0	|| navePos.y > HG_SCREEN || navePos.y < 0)
	{
		naveDir *= -1 ;

	}


	//navePos = mousePos;

	
		
}

void draw()
{
	C2D2_LimpaTela();

	C2D2_DesenhaSprite(nave, 0, navePos.x, navePos.y);
	
	C2D2_DesenhaSprite(mouseTx, 0, mousePos.x, mousePos.y);
	
	C2D2_DesenhaSprite(shield, 0, shieldPos.x, shieldPos.y);

	C2D2_DesenhaSprite(shield2, 0, shieldPos1.x, shieldPos1.y);


}

void dispose()
{
	//Libere recursos aqui
}

int main(int argc, char* argv[])
{
	if (!C2D2_Inicia(WD_SCREEN, HG_SCREEN, C2D2_JANELA, C2D2_DESENHO_OPENGL, "FISICA - VETORES"))
	{
		cout << "Não foi possível iniciar a Chien2D" << endl;
		exit(1);
	}

	setup();
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	unsigned long antes = C2D2_TempoSistema() - 1;
	while (!teclas[C2D2_ENCERRA].pressionado && !teclas[C2D2_ESC].pressionado)
	{
		float secs = (C2D2_TempoSistema() - antes) / 1000.0f;
		antes = C2D2_TempoSistema();
		update(secs);
		draw();
		C2D2_Sincroniza(C2D2_FPS_PADRAO);
	}
	dispose();

	C2D2_Encerra();
}