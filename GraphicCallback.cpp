//
//  GraphicCallback.cpp
//  BaseEngine
//
//  Created by memo on 19/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#include "glew.h"
#include "GraphicCallback.h"

Stopwatch swatch;
int nbFrames = 0;

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(SharedData::eyeX, SharedData::eyeY, SharedData::eyeZ, SharedData::centerX, SharedData::centerY, SharedData::centerZ, SharedData::upX, SharedData::upY, SharedData::upZ);



    //la map
    glBindTexture(GL_TEXTURE_2D, TextureBuilder::brickText);

    glBindBuffer(GL_ARRAY_BUFFER, SharedData::buffers[0]);
    glVertexPointer( 3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, SharedData::buffers[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SharedData::buffers[1]);

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDrawElements(GL_TRIANGLES,SharedData::IndiceArraySize, GL_UNSIGNED_INT, 0);

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    //les persos
    for (int i=0; i < SharedData::persos.size(); i++) {
        glPushMatrix();
        SharedData::persos[i]->affiche();
        glPopMatrix();
    }

    glutSwapBuffers();

    if (SharedData::fpsAffichage) {
        swatch.stop();
        int64_t tmp;
        if ((tmp = swatch.elapsed_ms()) > 200) {
            printf("%f fps\n",float(nbFrames) / tmp * 1000.);
            swatch.start();
            nbFrames = 0;
        }
        nbFrames++;
    }

}

void ReshapeCallback(int width, int height){
	glViewport(0,0,width,height);
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 	gluPerspective(45,float(width)/float(height),0.1,100);
 	glMatrixMode(GL_MODELVIEW);
}

