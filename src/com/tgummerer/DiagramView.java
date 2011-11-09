/*
 * Performance analysis
 * 
 * Doing the Java work for the OpenGL graphics, and calling the native methods
 * 
 * Copyright (c) Thomas Gummerer 2011 | All rights reserved
 */

package com.tgummerer;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class DiagramView extends GLSurfaceView {


    public DiagramView(Context context) {
        super(context);
        setRenderer(new DiagramRenderer());
    }

    private class DiagramRenderer implements GLSurfaceView.Renderer {

        private FloatBuffer triangleVB;
        
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            // Set the background frame color
            gl.glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            
            initShapes();
            gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
        }

        public void onDrawFrame(GL10 gl) {
            // Redraw background color
            gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
            gl.glColor4f(0.63671875f, 0.76953125f, 0.22265625f, 0.0f);
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, triangleVB);
            gl.glDrawArrays(GL10.GL_TRIANGLES, 0, 3);
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            gl.glViewport(0, 0, width, height);
        }

        private void initShapes(){

            float triangleCoords[] = {
                // X, Y, Z
                -0.5f, -0.25f, 0,
                0.5f, -0.25f, 0,
                0.0f,  0.559016994f, 0
            }; 

            // initialize vertex Buffer for triangle  
            ByteBuffer vbb = ByteBuffer.allocateDirect(
                    // (# of coordinate values * 4 bytes per float)
                    triangleCoords.length * 4); 
            vbb.order(ByteOrder.nativeOrder()); // use the device hardware's native byte order
            triangleVB = vbb.asFloatBuffer();  // create a floating point buffer from the ByteBuffer
            triangleVB.put(triangleCoords);    // add the coordinates to the FloatBuffer
            triangleVB.position(0);            // set the buffer to read the first coordinate

        }
    }
}
