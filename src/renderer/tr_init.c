/*
===========================================================================

Wolfenstein: Enemy Territory GPL Source Code
Copyright (C) 1999-2010 id Software LLC, a ZeniMax Media company. 

This file is part of the Wolfenstein: Enemy Territory GPL Source Code (Wolf ET Source Code).  

Wolf ET Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Wolf ET Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wolf ET Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Wolf: ET Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Wolf ET Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

// tr_init.c -- functions that are not called every frame

#include "tr_local.h"

glconfig_t	glConfig;
glconfigExt_t glConfigExt;
                
glstate_t	glState;

static void GfxInfo_f( void );

cvar_t  *r_flareSize;
cvar_t  *r_flareFade;

cvar_t  *r_railWidth;
cvar_t  *r_railCoreWidth;
cvar_t  *r_railSegmentLength;

cvar_t  *r_ignoreFastPath;

cvar_t  *r_verbose;
cvar_t  *r_ignore;

cvar_t  *r_displayRefresh;

cvar_t  *r_detailTextures;

cvar_t  *r_znear;
cvar_t  *r_zfar;
cvar_t	*r_zproj;
cvar_t	*r_stereoSeparation;

cvar_t  *r_skipBackEnd;

cvar_t	*r_stereoEnabled;
cvar_t	*r_anaglyphMode;

cvar_t	*r_greyscale;

cvar_t	*r_ignorehwgamma;

cvar_t  *r_inGameVideo;
cvar_t  *r_fastsky;
cvar_t	*r_neatsky;
cvar_t  *r_drawSun;
cvar_t  *r_dynamiclight;
#ifdef USE_PMLIGHT
cvar_t	*r_dlightMode;
cvar_t	*r_dlightSpecPower;
cvar_t	*r_dlightSpecColor;
cvar_t	*r_dlightScale;
cvar_t	*r_dlightIntensity;
cvar_t	*r_fbo;
#endif
cvar_t  *r_dlightBacks;

cvar_t  *r_lodbias;
cvar_t  *r_lodscale;

cvar_t  *r_norefresh;
cvar_t  *r_drawentities;
cvar_t  *r_drawworld;
cvar_t  *r_drawfoliage;     // ydnar
cvar_t  *r_speeds;
//cvar_t	*r_fullbright; // JPW NERVE removed per atvi request
cvar_t  *r_novis;
cvar_t  *r_nocull;
cvar_t  *r_facePlaneCull;
cvar_t  *r_showcluster;
cvar_t  *r_nocurves;

cvar_t  *r_allowExtensions;

cvar_t  *r_ext_compressed_textures;
cvar_t  *r_ext_gamma_control;
cvar_t  *r_ext_multitexture;
cvar_t  *r_ext_compiled_vertex_array;
cvar_t  *r_ext_texture_env_add;

cvar_t  *r_clampToEdge; // ydnar: opengl 1.2 GL_CLAMP_TO_EDGE SUPPORT

//----(SA)	added
cvar_t  *r_ext_texture_filter_anisotropic;

cvar_t  *r_ext_NV_fog_dist;
cvar_t  *r_nv_fogdist_mode;

cvar_t	*r_ext_max_anisotropy;

cvar_t  *r_ext_ATI_pntriangles;
cvar_t  *r_ati_truform_tess;        //
cvar_t  *r_ati_truform_normalmode;  // linear/quadratic
cvar_t  *r_ati_truform_pointmode;   // linear/cubic
//----(SA)	end

cvar_t  *r_ignoreGLErrors;
cvar_t  *r_logFile;

cvar_t	*r_stencilbits;
cvar_t	*r_depthbits;
cvar_t	*r_colorbits;
cvar_t	*r_primitives;
cvar_t	*r_texturebits;
cvar_t  *r_ext_multisample;

cvar_t  *r_drawBuffer;
cvar_t  *r_glDriver;
cvar_t  *r_glIgnoreWicked3D;
cvar_t  *r_lightmap;
cvar_t  *r_uiFullScreen;
cvar_t  *r_shadows;
cvar_t  *r_portalsky;   //----(SA)	added
cvar_t  *r_flares;
cvar_t  *r_mode;
cvar_t	*r_modeFullscreen;
cvar_t  *r_oldMode;     // ydnar
cvar_t  *r_nobind;
cvar_t  *r_singleShader;
cvar_t  *r_roundImagesDown;
cvar_t	*r_allowNonPo2;
cvar_t  *r_colorMipLevels;
cvar_t  *r_picmip;
cvar_t  *r_showtris;
cvar_t  *r_trisColor;
cvar_t  *r_showsky;
cvar_t  *r_shownormals;
cvar_t  *r_normallength;
cvar_t  *r_showmodelbounds;
cvar_t  *r_finish;
cvar_t  *r_clear;
cvar_t  *r_swapInterval;
cvar_t  *r_textureMode;
cvar_t  *r_offsetFactor;
cvar_t  *r_offsetUnits;
cvar_t  *r_gamma;
cvar_t  *r_intensity;
cvar_t  *r_lockpvs;
cvar_t  *r_noportals;
cvar_t  *r_portalOnly;

cvar_t  *r_subdivisions;
cvar_t  *r_lodCurveError;

cvar_t  *r_fullscreen;

cvar_t  *r_customwidth;
cvar_t  *r_customheight;
cvar_t  *r_customaspect;

cvar_t  *r_overBrightBits;
cvar_t  *r_mapOverBrightBits;
cvar_t	*r_mapGrayScale;

cvar_t  *r_debugSurface;
cvar_t  *r_simpleMipMaps;

cvar_t  *r_showImages;

cvar_t  *r_ambientScale;
cvar_t  *r_directedScale;
cvar_t  *r_debugLight;
cvar_t  *r_debugSort;
cvar_t  *r_printShaders;
cvar_t  *r_saveFontData;

// Ridah
cvar_t  *r_cache;
cvar_t  *r_cacheShaders;
cvar_t  *r_cacheModels;

cvar_t  *r_cacheGathering;

cvar_t  *r_buildScript;

cvar_t  *r_bonesDebug;
// done.

// Rafael - wolf fog
cvar_t  *r_wolffog;
// done

cvar_t  *r_highQualityVideo;

cvar_t	*r_aviMotionJpegQuality;
cvar_t	*r_screenshotJpegQuality;

cvar_t	*r_floatfix; // -EC-

cvar_t  *r_maxpolys;
int max_polys;
cvar_t  *r_maxpolyverts;
int max_polyverts;

void ( APIENTRY * qglMultiTexCoord2fARB )( GLenum texture, GLfloat s, GLfloat t );
void ( APIENTRY * qglActiveTextureARB )( GLenum texture );
void ( APIENTRY * qglClientActiveTextureARB )( GLenum texture );

void ( APIENTRY * qglLockArraysEXT )( GLint, GLint );
void ( APIENTRY * qglUnlockArraysEXT )( void );

//----(SA)	added
void ( APIENTRY * qglPNTrianglesiATI )( GLenum pname, GLint param );
void ( APIENTRY * qglPNTrianglesfATI )( GLenum pname, GLfloat param );
/*
The tessellation level and normal generation mode are specified with:

	void qglPNTriangles{if}ATI(enum pname, T param)

	If <pname> is:
		GL_PN_TRIANGLES_NORMAL_MODE_ATI -
			<param> must be one of the symbolic constants:
				- GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI or
				- GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI
			which will select linear or quadratic normal interpolation respectively.
		GL_PN_TRIANGLES_POINT_MODE_ATI -
			<param> must be one of the symbolic  constants:
				- GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI or
				- GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI
			which will select linear or cubic interpolation respectively.
		GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI -
			<param> should be a value specifying the number of evaluation points on each edge.  This value must be
			greater than 0 and less than or equal to the value given by GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI.

	An INVALID_VALUE error will be generated if the value for <param> is less than zero or greater than the max value.

Associated 'gets':
Get Value                               Get Command Type     Minimum Value								Attribute
---------                               ----------- ----     ------------								---------
PN_TRIANGLES_ATI						IsEnabled   B		False                                       PN Triangles/enable
PN_TRIANGLES_NORMAL_MODE_ATI			GetIntegerv Z2		PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI		PN Triangles
PN_TRIANGLES_POINT_MODE_ATI				GetIntegerv Z2		PN_TRIANGLES_POINT_MODE_CUBIC_ATI			PN Triangles
PN_TRIANGLES_TESSELATION_LEVEL_ATI		GetIntegerv Z+		1											PN Triangles
MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI	GetIntegerv Z+		1											-




*/
//----(SA)	end



/*
** InitOpenGL
**
** This function is responsible for initializing a valid OpenGL subsystem.  This
** is done by calling GLimp_Init (which gives us a working OGL subsystem) then
** setting variables, checking GL constants, and reporting the gfx system config
** to the user.
*/
static void InitOpenGL( void )
{
	//
	// initialize OS specific portions of the renderer
	//
	// GLimp_Init directly or indirectly references the following cvars:
	//		- r_fullscreen
	//		- r_mode
	//		- r_(color|depth|stencil)bits
	//		- r_ignorehwgamma
	//		- r_gamma
	//
	
	if ( glConfig.vidWidth == 0 )
	{
		GLint		temp;

		memset( &glConfig, 0, sizeof( glConfig ) );
		memset( &glConfigExt, 0, sizeof( glConfigExt ) );
		
		GLimp_Init();

		if ( !qglGetString( GL_EXTENSIONS ) )
		{
			Com_Error( ERR_FATAL, "OpenGL installation is broken. Please fix video drivers and/or restart your system" );
		}

		// OpenGL driver constants
		qglGetIntegerv( GL_MAX_TEXTURE_SIZE, &temp );
		glConfig.maxTextureSize = temp;

		if ( glConfig.maxActiveTextures > MAX_TEXTURE_UNITS )
			glConfig.maxActiveTextures = MAX_TEXTURE_UNITS;

		// stubbed or broken drivers may have reported 0...
		if ( glConfig.maxTextureSize <= 0 ) 
		{
			glConfig.maxTextureSize = 0;
		}
	}

	// print info
	GfxInfo_f();

	// set default state
	GL_SetDefaultState();
}


/*
==================
GL_CheckErrors
==================
*/
void GL_CheckErrors( void ) {
    int		err;
    const char *s;
    char buf[32];

    err = qglGetError();
    if ( err == GL_NO_ERROR ) {
        return;
    }
    if ( r_ignoreGLErrors->integer ) {
        return;
    }
    switch( err ) {
        case GL_INVALID_ENUM:
            s = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            s = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            s = "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            s = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            s = "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            s = "GL_OUT_OF_MEMORY";
            break;
        default:
            Com_sprintf( buf, sizeof(buf), "%i", err);
            s = buf;
            break;
    }

	ri.Error( ERR_VID_FATAL, "GL_CheckErrors: %s", s );
}


/*
** R_GetModeInfo
*/
typedef struct vidmode_s
{
    const char *description;
    int         width, height;
	float		pixelAspect;		// pixel width / height
} vidmode_t;

vidmode_t r_vidModes[] =
{
	{ "Mode  0: 320x240",			320,	240,	1 },
	{ "Mode  1: 400x300",			400,	300,	1 },
	{ "Mode  2: 512x384",			512,	384,	1 },
	{ "Mode  3: 640x480",			640,	480,	1 },
	{ "Mode  4: 800x600",			800,	600,	1 },
	{ "Mode  5: 960x720",			960,	720,	1 },
	{ "Mode  6: 1024x768",			1024,	768,	1 },
	{ "Mode  7: 1152x864",			1152,	864,	1 },
	{ "Mode  8: 1280x1024 (5:4)",	1280,	1024,	1 },
	{ "Mode  9: 1600x1200",			1600,	1200,	1 },
	{ "Mode 10: 2048x1536",			2048,	1536,	1 },
	{ "Mode 11: 856x480 (wide)",	856,	480,	1 },
	// extra modes:
	{ "Mode 12: 1280x960",			1280,	960,	1 },
	{ "Mode 13: 1280x720",			1280,	720,	1 },
	{ "Mode 14: 1280x800 (16:10)",	1280,	800,	1 },
	{ "Mode 15: 1366x768",			1366,	768,	1 },
	{ "Mode 16: 1440x900 (16:10)",	1440,	900,	1 },
	{ "Mode 17: 1600x900",			1600,	900,	1 },
	{ "Mode 18: 1680x1050 (16:10)",	1680,	1050,	1 },
	{ "Mode 19: 1920x1080",			1920,	1080,	1 },
	{ "Mode 20: 1920x1200 (16:10)",	1920,	1200,	1 },
	{ "Mode 21: 2560x1080 (21:9)",	2560,	1080,	1 },
	{ "Mode 22: 3440x1440 (21:9)",	3440,	1440,	1 },
	{ "Mode 23: 3840x2160",			3840,	2160,	1 },
	{ "Mode 24: 4096x2160 (4K)",	4096,	2160,	1 }
};
static int	s_numVidModes = ARRAY_LEN( r_vidModes );

qboolean R_GetModeInfo( int *width, int *height, float *windowAspect, int mode, const char *modeFS, int dw, int dh, qboolean fullscreen ) {
	vidmode_t	*vm;
	float		pixelAspect;

	// set dedicated fullscreen mode
	if ( fullscreen && *modeFS )
		mode = atoi( modeFS );

	if ( mode < -2 )
		return qfalse;

	if ( mode >= s_numVidModes )
		return qfalse;

	// fix unknown desktop resolution
	if ( mode == -2 && (dw == 0 || dh == 0) ) 
		mode = 3;

	if ( mode == -2 ) { // desktop resolution
		*width = dw;
		*height = dh;
		pixelAspect = r_customaspect->value;
	} else if ( mode == -1 ) { // custom resolution
		*width = r_customwidth->integer;
		*height = r_customheight->integer;
		pixelAspect = r_customaspect->value;
	} else { // predefined resolution
		vm = &r_vidModes[ mode ];
		*width  = vm->width;
		*height = vm->height;
		pixelAspect = vm->pixelAspect;
	}

	*windowAspect = (float)*width / ( *height * pixelAspect );

	return qtrue;
}

/*
** R_ModeList_f
*/
static void R_ModeList_f( void )
{
	int i;

	ri.Printf( PRINT_ALL, "\n" );
	for ( i = 0; i < s_numVidModes; i++ )
	{
		ri.Printf( PRINT_ALL, "%s\n", r_vidModes[i].description );
	}
	ri.Printf( PRINT_ALL, "\n" );
}


/*
==============================================================================

						SCREEN SHOTS

==============================================================================
*/

/* 
================== 
RB_ReadPixels

Reads an image but takes care of alignment issues for reading RGB images.

Reads a minimum offset for where the RGB data starts in the image from
integer stored at pointer offset. When the function has returned the actual
offset was written back to address offset. This address will always have an
alignment of packAlign to ensure efficient copying.

Stores the length of padding after a line of pixels to address padlen

Return value must be freed with ri.Hunk_FreeTempMemory()
================== 
*/  
byte *RB_ReadPixels(int x, int y, int width, int height, size_t *offset, int *padlen)
{
	byte *buffer, *bufstart;
	int padwidth, linelen;
	GLint packAlign;
	
	qglGetIntegerv(GL_PACK_ALIGNMENT, &packAlign);
	
	linelen = width * 3;
	padwidth = PAD(linelen, packAlign);
	
	// Allocate a few more bytes so that we can choose an alignment we like
	buffer = ri.Hunk_AllocateTempMemory(padwidth * height + *offset + packAlign - 1);
	
	bufstart = PADP((intptr_t) buffer + *offset, packAlign);
	qglReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, bufstart);
	
	*offset = bufstart - buffer;
	*padlen = padwidth - linelen;
	
	return buffer;
}


/* 
================== 
RB_TakeScreenshot
================== 
*/  
void RB_TakeScreenshot( int x, int y, int width, int height, const char *fileName )
{
	byte *allbuf, *buffer;
	byte *srcptr, *destptr;
	byte *endline, *endmem;
	byte temp;
	
	int linelen, padlen;
	size_t offset = 18, memcount;
		
	allbuf = RB_ReadPixels(x, y, width, height, &offset, &padlen);
	buffer = allbuf + offset - 18;
	
	Com_Memset (buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = width & 255;
	buffer[13] = width >> 8;
	buffer[14] = height & 255;
	buffer[15] = height >> 8;
	buffer[16] = 24;	// pixel size

	// swap rgb to bgr and remove padding from line endings
	linelen = width * 3;
	
	srcptr = destptr = allbuf + offset;
	endmem = srcptr + (linelen + padlen) * height;
	
	while(srcptr < endmem)
	{
		endline = srcptr + linelen;

		while(srcptr < endline)
		{
			temp = srcptr[0];
			*destptr++ = srcptr[2];
			*destptr++ = srcptr[1];
			*destptr++ = temp;
			
			srcptr += 3;
		}
		
		// Skip the pad
		srcptr += padlen;
	}

	memcount = linelen * height;

	// gamma correct
	if(glConfig.deviceSupportsGamma)
		R_GammaCorrect(allbuf + offset, memcount);

	ri.FS_WriteFile(fileName, buffer, memcount + 18);

	ri.Hunk_FreeTempMemory(allbuf);
}


/* 
================== 
RB_TakeScreenshotJPEG
================== 
*/
void RB_TakeScreenshotJPEG( int x, int y, int width, int height, const char *fileName )
{
	byte *buffer;
	size_t offset = 0, memcount;
	int padlen;

	buffer = RB_ReadPixels(x, y, width, height, &offset, &padlen);
	memcount = (width * 3 + padlen) * height;

	// gamma correct
	if(glConfig.deviceSupportsGamma)
		R_GammaCorrect(buffer + offset, memcount);

	RE_SaveJPG(fileName, r_screenshotJpegQuality->integer, width, height, buffer + offset, padlen);
	ri.Hunk_FreeTempMemory(buffer);
}


/*
==================
RB_TakeScreenshotCmd
==================
*/
const void *RB_TakeScreenshotCmd( const void *data ) {
	const screenshotCommand_t	*cmd;
	
	cmd = (const screenshotCommand_t *)data;
	
	if (cmd->jpeg)
		RB_TakeScreenshotJPEG( cmd->x, cmd->y, cmd->width, cmd->height, cmd->fileName);
	else
		RB_TakeScreenshot( cmd->x, cmd->y, cmd->width, cmd->height, cmd->fileName);
	
	return (const void *)(cmd + 1);	

}


/* 
================== 
R_ScreenshotFilename
================== 
*/  
static void R_ScreenshotFilename( char *fileName, const char *fileExt ) {
	qtime_t t;
	int count;

	count = 0;
	Com_RealTime( &t );

	Com_sprintf( fileName, MAX_OSPATH, "screenshots/shot-%04d%02d%02d-%02d%02d%02d.%s", 
			1900 + t.tm_year, 1 + t.tm_mon,	t.tm_mday,
			t.tm_hour, t.tm_min, t.tm_sec, fileExt );

	while (	ri.FS_FileExists( fileName ) && ++count < 1000 ) {
		Com_sprintf( fileName, MAX_OSPATH, "screenshots/shot-%04d%02d%02d-%02d%02d%02d-%d.%s", 
				1900 + t.tm_year, 1 + t.tm_mon,	t.tm_mday,
				t.tm_hour, t.tm_min, t.tm_sec, count, fileExt );
	}
}


/*
====================
R_LevelShot

levelshots are specialized 128*128 thumbnails for
the menu system, sampled down from full screen distorted images
====================
*/
void R_LevelShot( void ) {
	char		checkname[MAX_OSPATH];
	byte		*buffer;
	byte		*source, *allsource;
	byte		*src, *dst;
	size_t			offset = 0;
	int			padlen;
	int			x, y;
	int			r, g, b;
	float		xScale, yScale;
	int			xx, yy;

	Com_sprintf(checkname, sizeof(checkname), "levelshots/%s.tga", tr.world->baseName);

	allsource = RB_ReadPixels(0, 0, glConfig.vidWidth, glConfig.vidHeight, &offset, &padlen);
	source = allsource + offset;

	buffer = ri.Hunk_AllocateTempMemory(128 * 128*3 + 18);
	Com_Memset (buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = 128;
	buffer[14] = 128;
	buffer[16] = 24;	// pixel size

	// resample from source
	xScale = glConfig.vidWidth / 512.0f;
	yScale = glConfig.vidHeight / 384.0f;
	for ( y = 0 ; y < 128 ; y++ ) {
		for ( x = 0 ; x < 128 ; x++ ) {
			r = g = b = 0;
			for ( yy = 0 ; yy < 3 ; yy++ ) {
				for ( xx = 0 ; xx < 4 ; xx++ ) {
					src = source + (3 * glConfig.vidWidth + padlen) * (int)((y*3 + yy) * yScale) +
						3 * (int) ((x*4 + xx) * xScale);
					r += src[0];
					g += src[1];
					b += src[2];
				}
			}
			dst = buffer + 18 + 3 * ( y * 128 + x );
			dst[0] = b / 12;
			dst[1] = g / 12;
			dst[2] = r / 12;
		}
	}

	// gamma correct
	if ( glConfig.deviceSupportsGamma ) {
		R_GammaCorrect( buffer + 18, 128 * 128 * 3 );
	}

	ri.FS_WriteFile( checkname, buffer, 128 * 128*3 + 18 );

	ri.Hunk_FreeTempMemory(buffer);
	ri.Hunk_FreeTempMemory(allsource);

	ri.Printf( PRINT_ALL, "Wrote %s\n", checkname );
}


/* 
================== 
R_ScreenShot_f

screenshot
screenshot [silent]
screenshot [levelshot]
screenshot [filename]

Doesn't print the pacifier message if there is a second arg
================== 
*/  
void R_ScreenShot_f( void ) {
	char		checkname[MAX_OSPATH];
	qboolean	silent;
	int			typeMask;
	const char	*ext;

	if ( !strcmp( ri.Cmd_Argv(1), "levelshot" ) ) {
		R_LevelShot();
		return;
	}

	if ( Q_stricmp( ri.Cmd_Argv(0), "screenshotJPEG" ) == 0 ) {
		typeMask = SCREENSHOT_JPG;
		ext = "jpg";
	} else {
		typeMask = SCREENSHOT_TGA;
		ext = "tga";
	}

	// check if already scheduled
	if ( backEnd.screenshotMask & typeMask )
		return;

	if ( !strcmp( ri.Cmd_Argv(1), "silent" ) ) {
		silent = qtrue;
	} else {
		silent = qfalse;
	}

	if ( ri.Cmd_Argc() == 2 && !silent ) {
		// explicit filename
		Com_sprintf( checkname, MAX_OSPATH, "screenshots/%s.%s", ri.Cmd_Argv( 1 ), ext );
	} else {
		// scan for a free filename
		R_ScreenshotFilename( checkname, ext );
	}

#if 1
	// we will make screenshot right at the end of RE_EndFrame()
	backEnd.screenshotMask |= typeMask;
	if ( typeMask == SCREENSHOT_JPG ) {
		Q_strncpyz( backEnd.screenshotJPG, checkname, sizeof( backEnd.screenshotJPG ) );
	} else {
		Q_strncpyz( backEnd.screenshotTGA, checkname, sizeof( backEnd.screenshotTGA ) );
	}
#else
	R_TakeScreenshot( 0, 0, glConfig.vidWidth, glConfig.vidHeight, checkname, typeMask == SCREENSHOT_JPG );
#endif

	if ( !silent ) {
		ri.Printf (PRINT_ALL, "Wrote %s\n", checkname);
	}
} 


//============================================================================

/*
==================
RB_TakeVideoFrameCmd
==================
*/
const void *RB_TakeVideoFrameCmd( const void *data )
{
	const videoFrameCommand_t	*cmd;
	byte				*cBuf;
	size_t				memcount, linelen;
	int				padwidth, avipadwidth, padlen, avipadlen;
	GLint packAlign;
	
	cmd = (const videoFrameCommand_t *)data;
	
	qglGetIntegerv(GL_PACK_ALIGNMENT, &packAlign);

	linelen = cmd->width * 3;

	// Alignment stuff for glReadPixels
	padwidth = PAD(linelen, packAlign);
	padlen = padwidth - linelen;
	// AVI line padding
	avipadwidth = PAD(linelen, AVI_LINE_PADDING);
	avipadlen = avipadwidth - linelen;

	cBuf = PADP(cmd->captureBuffer, packAlign);
		
	qglReadPixels(0, 0, cmd->width, cmd->height, GL_RGB,
		GL_UNSIGNED_BYTE, cBuf);

	memcount = padwidth * cmd->height;

	// gamma correct
	if(glConfig.deviceSupportsGamma)
		R_GammaCorrect(cBuf, memcount);

	if(cmd->motionJpeg)
	{
		memcount = RE_SaveJPGToBuffer(cmd->encodeBuffer, linelen * cmd->height,
			r_aviMotionJpegQuality->integer,
			cmd->width, cmd->height, cBuf, padlen);
		ri.CL_WriteAVIVideoFrame(cmd->encodeBuffer, memcount);
	}
	else
	{
		byte *lineend, *memend;
		byte *srcptr, *destptr;
	
		srcptr = cBuf;
		destptr = cmd->encodeBuffer;
		memend = srcptr + memcount;
		
		// swap R and B and remove line paddings
		while(srcptr < memend)
		{
			lineend = srcptr + linelen;
			while(srcptr < lineend)
			{
				*destptr++ = srcptr[2];
				*destptr++ = srcptr[1];
				*destptr++ = srcptr[0];
				srcptr += 3;
			}
			
			Com_Memset(destptr, '\0', avipadlen);
			destptr += avipadlen;
			
			srcptr += padlen;
		}
		
		ri.CL_WriteAVIVideoFrame(cmd->encodeBuffer, avipadwidth * cmd->height);
	}

	return (const void *)(cmd + 1);	
}


//============================================================================

/*
** GL_SetDefaultState
*/
void GL_SetDefaultState( void )
{
	qglClearDepth( 1.0f );

	qglCullFace(GL_FRONT);

	qglColor4f (1,1,1,1);

	// initialize downstream texture unit if we're running
	// in a multitexture environment
	if ( qglActiveTextureARB ) {
		GL_SelectTexture( 1 );
		GL_TextureMode( r_textureMode->string );
		GL_TexEnv( GL_MODULATE );
		qglDisable( GL_TEXTURE_2D );
		GL_SelectTexture( 0 );
	}

	qglEnable(GL_TEXTURE_2D);
	GL_TextureMode( r_textureMode->string );
	GL_TexEnv( GL_MODULATE );

	qglShadeModel( GL_SMOOTH );
	qglDepthFunc( GL_LEQUAL );

	// the vertex array is always enabled, but the color and texture
	// arrays are enabled and disabled around the compiled vertex array call
	qglEnableClientState (GL_VERTEX_ARRAY);

	//
	// make sure our GL state vector is set correctly
	//
	glState.glStateBits = GLS_DEPTHTEST_DISABLE | GLS_DEPTHMASK_TRUE;

	qglPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	qglDepthMask( GL_TRUE );
	qglDisable( GL_DEPTH_TEST );
	qglEnable( GL_SCISSOR_TEST );
	qglDisable( GL_CULL_FACE );
	qglDisable( GL_BLEND );

//----(SA)	added.
	// ATI pn_triangles
	if ( qglPNTrianglesiATI ) {
		int maxtess;
		// get max supported tesselation
		qglGetIntegerv( GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI, (GLint*)&maxtess );
#ifdef __MACOS__
		glConfig.ATIMaxTruformTess = 7;
#else
		glConfig.ATIMaxTruformTess = maxtess;
#endif
		// cap if necessary
		if ( r_ati_truform_tess->value > maxtess ) {
			ri.Cvar_Set( "r_ati_truform_tess", va( "%d", maxtess ) );
		}

		// set Wolf defaults
		qglPNTrianglesiATI( GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI, r_ati_truform_tess->value );
	}

//----(SA)	end
}

/*
================
R_PrintLongString

Workaround for ri.Printf's 1024 characters buffer limit.
================
*/
void R_PrintLongString(int printMode, const char *string) {
	char buffer[1024];
	const char *p = string;
	int remainingLength = strlen( string );
	
	// ENSI TODO clamp printMode PRINT_ALL ... PRINT_WARNING

	while (remainingLength > 0)
	{
		// Take as much characters as possible from the string without splitting words between buffers
		// This avoids the client console splitting a word up when one half fits on the current line,
		// but the second half would have to be written on a new line
		int charsToTake = sizeof(buffer) - 1;
		if (remainingLength > charsToTake) {
			while (p[charsToTake - 1] > ' ' && p[charsToTake] > ' ') {
				charsToTake--;
				if (charsToTake == 0) {
					charsToTake = sizeof(buffer) - 1;
					break;
				}
			}
		} else if (remainingLength < charsToTake) {
			charsToTake = remainingLength;
		}

		Q_strncpyz( buffer, p, charsToTake + 1 );
		ri.Printf( printMode, "%s", buffer );
		remainingLength -= charsToTake;
		p += charsToTake;
	}
}


/*
================
GfxInfo_f
================
*/
void GfxInfo_f( void ) 
{
	cvar_t *sys_cpustring = ri.Cvar_Get( "sys_cpustring", "", 0 );
	const char *enablestrings[] =
	{
		"disabled",
		"enabled"
	};
	const char *fsstrings[] =
	{
		"windowed",
		"fullscreen"
	};
	const char *tc_table[] =
	{
		"None",
		"GL_S3_s3tc",
		"GL_EXT_texture_compression_s3tc",
	};

	ri.Printf( PRINT_ALL, "\nGL_VENDOR: %s\n", glConfig.vendor_string );
	ri.Printf( PRINT_ALL, "GL_RENDERER: %s\n", glConfig.renderer_string );
	ri.Printf( PRINT_ALL, "GL_VERSION: %s\n", glConfig.version_string );
	ri.Printf( PRINT_DEVELOPER, "GL_EXTENSIONS: " );
	R_PrintLongString( PRINT_DEVELOPER, glConfigExt.originalExtensionString );
	ri.Printf( PRINT_DEVELOPER, "\n" );
	ri.Printf( PRINT_ALL, "GL_MAX_TEXTURE_SIZE: %d\n", glConfig.maxTextureSize );
	ri.Printf( PRINT_ALL, "GL_MAX_ACTIVE_TEXTURES_ARB: %d\n", glConfig.maxActiveTextures );
	ri.Printf( PRINT_ALL, "\nPIXELFORMAT: color(%d-bits) Z(%d-bit) stencil(%d-bits)\n", glConfig.colorBits, glConfig.depthBits, glConfig.stencilBits );
	ri.Printf( PRINT_ALL, "MODE: %d, %d x %d %s hz:", r_mode->integer, glConfig.vidWidth, glConfig.vidHeight, fsstrings[r_fullscreen->integer != 0] );
	if ( glConfig.displayFrequency )
	{
		ri.Printf( PRINT_ALL, "%d\n", glConfig.displayFrequency );
	}
	else
	{
		ri.Printf( PRINT_ALL, "N/A\n" );
	}
	if ( glConfig.deviceSupportsGamma )
	{
		ri.Printf( PRINT_ALL, "GAMMA: hardware w/ %d overbright bits\n", tr.overbrightBits );
	}
	else
	{
		ri.Printf( PRINT_ALL, "GAMMA: software w/ %d overbright bits\n", tr.overbrightBits );
	}

	ri.Printf( PRINT_ALL, "CPU: %s\n", sys_cpustring->string );

	// rendering primitives
	{
		int		primitives;

		// default is to use triangles if compiled vertex arrays are present
		ri.Printf( PRINT_ALL, "rendering primitives: " );
		primitives = r_primitives->integer;
		if ( primitives == 0 ) {
			if ( qglLockArraysEXT ) {
				primitives = 2;
			} else {
				primitives = 1;
			}
		}
		if ( primitives == -1 ) {
			ri.Printf( PRINT_ALL, "none\n" );
		} else if ( primitives == 2 ) {
			ri.Printf( PRINT_ALL, "single glDrawElements\n" );
		} else if ( primitives == 1 ) {
			ri.Printf( PRINT_ALL, "multiple glArrayElement\n" );
		} else if ( primitives == 3 ) {
			ri.Printf( PRINT_ALL, "multiple glColor4ubv + glTexCoord2fv + glVertex3fv\n" );
		}
	}

	ri.Printf( PRINT_ALL, "texturemode: %s\n", r_textureMode->string );
	ri.Printf( PRINT_ALL, "picmip: %d\n", r_picmip->integer );
	ri.Printf( PRINT_ALL, "texture bits: %d\n", r_texturebits->integer );
	ri.Printf( PRINT_ALL, "multitexture: %s\n", enablestrings[qglActiveTextureARB != 0] );
	ri.Printf( PRINT_ALL, "compiled vertex arrays: %s\n", enablestrings[qglLockArraysEXT != 0 ] );
	ri.Printf( PRINT_ALL, "texenv add: %s\n", enablestrings[glConfig.textureEnvAddAvailable != 0] );
	ri.Printf( PRINT_ALL, "compressed textures: %s\n", enablestrings[glConfig.textureCompression != TC_NONE] );
	if ( glConfig.textureCompression != TC_NONE )
		ri.Printf( PRINT_ALL, "texture compression method: %s\n", tc_table[glConfig.textureCompression] );
	ri.Printf( PRINT_ALL, "anisotropic filtering: %s  ", enablestrings[(r_ext_texture_filter_anisotropic->integer != 0) && glConfig.maxAnisotropy] );
	if (r_ext_texture_filter_anisotropic->integer != 0 && glConfig.maxAnisotropy)
	{
		if (Q_isintegral(r_ext_texture_filter_anisotropic->value))
			ri.Printf( PRINT_ALL, "(%i of ", (int)r_ext_texture_filter_anisotropic->value);
		else
			ri.Printf( PRINT_ALL, "(%f of ", r_ext_texture_filter_anisotropic->value);

		if (Q_isintegral(glConfig.maxAnisotropy))
			ri.Printf( PRINT_ALL, "%i)\n", (int)glConfig.maxAnisotropy);
		else
			ri.Printf( PRINT_ALL, "%f)\n", glConfig.maxAnisotropy);
	}

	ri.Printf( PRINT_ALL, "NV distance fog: %s\n", enablestrings[glConfig.NVFogAvailable != 0] );
	if ( glConfig.NVFogAvailable ) {
		ri.Printf( PRINT_ALL, "Fog Mode: %s\n", r_nv_fogdist_mode->string );
	}

	if ( glConfig.hardwareType == GLHW_PERMEDIA2 ) {
		ri.Printf( PRINT_ALL, "HACK: using vertex lightmap approximation\n" );
	}
	if ( glConfig.hardwareType == GLHW_RAGEPRO )
	{
		ri.Printf( PRINT_ALL, "HACK: ragePro approximations\n" );
	}
	if ( glConfig.hardwareType == GLHW_RIVA128 )
	{
		ri.Printf( PRINT_ALL, "HACK: riva128 approximations\n" );
	}
	if ( r_finish->integer ) {
		ri.Printf( PRINT_ALL, "Forcing glFinish\n" );
	}
}


/*
===============
R_Register
===============
*/
void R_Register( void ) 
{
	//
	// latched and archived variables
	//
	r_glDriver = ri.Cvar_Get( "r_glDriver", OPENGL_DRIVER_NAME, CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_allowExtensions = ri.Cvar_Get( "r_allowExtensions", "1", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_ext_compressed_textures = ri.Cvar_Get( "r_ext_compressed_textures", "1", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE ); // (SA) ew, a spelling change I missed from the missionpack
	r_ext_gamma_control = ri.Cvar_Get( "r_ext_gamma_control", "1", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_ext_multitexture = ri.Cvar_Get( "r_ext_multitexture", "1", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_ext_compiled_vertex_array = ri.Cvar_Get( "r_ext_compiled_vertex_array", "1", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );

//----(SA)	added
	r_ext_ATI_pntriangles           = ri.Cvar_Get( "r_ext_ATI_pntriangles", "0", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE ); //----(SA)	default to '0'
	r_ati_truform_tess              = ri.Cvar_Get( "r_ati_truform_tess", "1", CVAR_ARCHIVE | CVAR_UNSAFE );
	r_ati_truform_normalmode        = ri.Cvar_Get( "r_ati_truform_normalmode", "GL_PN_TRIANGLES_NORMAL_MODE_LINEAR", CVAR_ARCHIVE | CVAR_UNSAFE );
	r_ati_truform_pointmode         = ri.Cvar_Get( "r_ati_truform_pointmode", "GL_PN_TRIANGLES_POINT_MODE_LINEAR", CVAR_ARCHIVE | CVAR_UNSAFE );

	r_ext_texture_filter_anisotropic    = ri.Cvar_Get( "r_ext_texture_filter_anisotropic", "0", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_ext_max_anisotropy = ri.Cvar_Get( "r_ext_max_anisotropy", "2", CVAR_ARCHIVE_ND | CVAR_LATCH );

	r_ext_NV_fog_dist                   = ri.Cvar_Get( "r_ext_NV_fog_dist", "0", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE );
	r_nv_fogdist_mode                   = ri.Cvar_Get( "r_nv_fogdist_mode", "GL_EYE_RADIAL_NV", CVAR_ARCHIVE | CVAR_UNSAFE );  // default to 'looking good'
//----(SA)	end

	r_ext_texture_env_add = ri.Cvar_Get( "r_ext_texture_env_add", "1", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );

	r_clampToEdge = ri.Cvar_Get( "r_clampToEdge", "1", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE ); // ydnar: opengl 1.2 GL_CLAMP_TO_EDGE support

	r_picmip = ri.Cvar_Get( "r_picmip", "1", CVAR_ARCHIVE | CVAR_LATCH ); //----(SA)	mod for DM and DK for id build.  was "1" // JPW NERVE pushed back to 1
	r_neatsky = ri.Cvar_Get( "r_neatsky", "1", CVAR_ARCHIVE | CVAR_LATCH | CVAR_NODEFAULT );
	r_roundImagesDown = ri.Cvar_Get( "r_roundImagesDown", "1", CVAR_ARCHIVE_ND | CVAR_LATCH );
	r_allowNonPo2 = ri.Cvar_Get( "r_allowNonPo2", "0", CVAR_ARCHIVE_ND | CVAR_LATCH );
	ri.Cvar_SetDescription( r_allowNonPo2, "Toggle to allow non power of two textures. Default is off like ETmain" );
	r_colorMipLevels = ri.Cvar_Get( "r_colorMipLevels", "0", CVAR_LATCH );
	ri.Cvar_CheckRange( r_picmip, -16, 16, qtrue );
	r_detailTextures = ri.Cvar_Get( "r_detailtextures", "1", CVAR_ARCHIVE_ND | CVAR_LATCH );
	r_texturebits = ri.Cvar_Get( "r_texturebits", "0", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_colorbits = ri.Cvar_Get( "r_colorbits", "0", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_stencilbits = ri.Cvar_Get( "r_stencilbits", "0", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_depthbits = ri.Cvar_Get( "r_depthbits", "0", CVAR_ARCHIVE_ND | CVAR_LATCH | CVAR_UNSAFE );
	r_ext_multisample = ri.Cvar_Get( "r_ext_multisample", "0", CVAR_ARCHIVE_ND | CVAR_LATCH );
	ri.Cvar_CheckRange( r_ext_multisample, 0, 8, qtrue );
	r_overBrightBits = ri.Cvar_Get( "r_overBrightBits", "0", CVAR_ARCHIVE_ND | CVAR_LATCH ); // Arnout: disable overbrightbits by default
	ri.Cvar_CheckRange( r_overBrightBits, 0, 1, qtrue );                                   // ydnar: limit to overbrightbits 1 (sorry 1337 players)
	r_ignorehwgamma = ri.Cvar_Get( "r_ignorehwgamma", "0", CVAR_ARCHIVE_ND | CVAR_LATCH );        // ydnar: use hw gamma by default
	r_mode = ri.Cvar_Get( "r_mode", "4", CVAR_ARCHIVE | CVAR_LATCH | CVAR_UNSAFE );
	r_modeFullscreen = ri.Cvar_Get( "r_modeFullscreen", "-2", CVAR_ARCHIVE | CVAR_LATCH );
	r_oldMode = ri.Cvar_Get( "r_oldMode", "", CVAR_ARCHIVE );                             // ydnar: previous "good" video mode
	r_fullscreen = ri.Cvar_Get( "r_fullscreen", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_customwidth = ri.Cvar_Get( "r_customwidth", "1600", CVAR_ARCHIVE | CVAR_LATCH );
	r_customheight = ri.Cvar_Get( "r_customheight", "1024", CVAR_ARCHIVE | CVAR_LATCH );
	r_customaspect = ri.Cvar_Get( "r_customaspect", "1", CVAR_ARCHIVE_ND | CVAR_LATCH );
	r_simpleMipMaps = ri.Cvar_Get( "r_simpleMipMaps", "1", CVAR_ARCHIVE_ND | CVAR_LATCH );
	r_uiFullScreen = ri.Cvar_Get( "r_uifullscreen", "0", 0 );
	r_subdivisions = ri.Cvar_Get( "r_subdivisions", "4", CVAR_ARCHIVE_ND | CVAR_LATCH );
	r_stereoEnabled = ri.Cvar_Get( "r_stereoEnabled", "0", CVAR_ARCHIVE_ND | CVAR_LATCH );
	r_ignoreFastPath = ri.Cvar_Get( "r_ignoreFastPath", "0", CVAR_ARCHIVE_ND | CVAR_LATCH ); // ydnar: use fast path by default
	r_greyscale = ri.Cvar_Get( "r_greyscale", "0", CVAR_ARCHIVE_ND | CVAR_LATCH );
	ri.Cvar_CheckRange( r_greyscale, 0, 1, qfalse );
	r_mapGrayScale = ri.Cvar_Get( "r_mapGrayScale", "0", CVAR_ARCHIVE_ND | CVAR_LATCH );
	ri.Cvar_CheckRange( r_mapGrayScale, 0, 1, qfalse );

	//
	// temporary latched variables that can only change over a restart
	//
	r_displayRefresh = ri.Cvar_Get( "r_displayRefresh", "0", CVAR_LATCH | CVAR_UNSAFE );
	ri.Cvar_CheckRange( r_displayRefresh, 0, 250, qtrue );
	r_mapOverBrightBits = ri.Cvar_Get( "r_mapOverBrightBits", "2", CVAR_ARCHIVE_ND | CVAR_LATCH );
	ri.Cvar_CheckRange( r_mapOverBrightBits, 0, 3, qtrue );
	r_intensity = ri.Cvar_Get( "r_intensity", "1", CVAR_LATCH );
	ri.Cvar_CheckRange( r_intensity, 1.0f, 1.5f, qfalse ); // ri.Cvar_CheckRange( r_intensity, 1.0f, 255.0f, qfalse );
	r_singleShader = ri.Cvar_Get( "r_singleShader", "0", CVAR_CHEAT | CVAR_LATCH );

	//
	// archived variables that can change at any time
	//
	r_lodCurveError = ri.Cvar_Get( "r_lodCurveError", "250", CVAR_ARCHIVE_ND );
	r_lodbias = ri.Cvar_Get( "r_lodbias", "0", CVAR_ARCHIVE_ND );
	r_flares = ri.Cvar_Get( "r_flares", "1", CVAR_ARCHIVE_ND | CVAR_LATCH );
	r_znear = ri.Cvar_Get( "r_znear", "3", CVAR_CHEAT );  // ydnar: changed it to 3 (from 4) because of lean/fov cheats
	ri.Cvar_CheckRange( r_znear, 0.001f, 200, qfalse );
//----(SA)	added
	r_zfar = ri.Cvar_Get( "r_zfar", "0", CVAR_CHEAT );
//----(SA)	end
	r_zproj = ri.Cvar_Get( "r_zproj", "64", CVAR_ARCHIVE_ND );
	r_stereoSeparation = ri.Cvar_Get( "r_stereoSeparation", "64", CVAR_ARCHIVE_ND );
	r_ignoreGLErrors = ri.Cvar_Get( "r_ignoreGLErrors", "1", CVAR_ARCHIVE_ND );
	r_fastsky = ri.Cvar_Get( "r_fastsky", "0", CVAR_ARCHIVE_ND );
	r_inGameVideo = ri.Cvar_Get( "r_inGameVideo", "1", CVAR_ARCHIVE_ND );
	r_drawSun = ri.Cvar_Get( "r_drawSun", "1", CVAR_ARCHIVE_ND );
	r_dynamiclight = ri.Cvar_Get( "r_dynamiclight", "1", CVAR_ARCHIVE );
#ifdef USE_PMLIGHT
	r_dlightMode = ri.Cvar_Get( "r_dlightMode", "1", CVAR_ARCHIVE );
#ifdef USE_LEGACY_DLIGHTS
	ri.Cvar_CheckRange( r_dlightMode, 0, 2, qtrue );
#else
	ri.Cvar_CheckRange( r_dlightMode, 1, 2, qtrue );
#endif
	r_dlightScale = ri.Cvar_Get( "r_dlightScale", "1.0", CVAR_ARCHIVE_ND );
	ri.Cvar_CheckRange( r_dlightScale, 0.1f, 1.0f, qfalse );
	r_dlightSpecPower = ri.Cvar_Get( "r_dlightSpecPower", "8.0", CVAR_ARCHIVE_ND );
	ri.Cvar_CheckRange( r_dlightSpecPower, 1.0f, 32.0f, qfalse );
	r_dlightSpecColor = ri.Cvar_Get( "r_dlightSpecColor", "-0.25", CVAR_ARCHIVE_ND );
	ri.Cvar_CheckRange( r_dlightSpecColor, -1.0f, 1.0f, qfalse );
	r_dlightIntensity = ri.Cvar_Get( "r_dlightIntensity", "1.0", CVAR_ARCHIVE_ND );
	ri.Cvar_CheckRange( r_dlightIntensity, 0.1f, 1.0f, qfalse );

	r_fbo = ri.Cvar_Get( "r_fbo", "0", CVAR_ARCHIVE | CVAR_LATCH );
#endif
	r_dlightBacks = ri.Cvar_Get( "r_dlightBacks", "1", CVAR_ARCHIVE_ND );
	r_finish = ri.Cvar_Get( "r_finish", "0", CVAR_ARCHIVE_ND );
	r_textureMode = ri.Cvar_Get( "r_textureMode", "GL_LINEAR_MIPMAP_NEAREST", CVAR_ARCHIVE );
	r_swapInterval = ri.Cvar_Get( "r_swapInterval", "0", CVAR_ARCHIVE_ND );
#ifdef __MACOS__
	r_gamma = ri.Cvar_Get( "r_gamma", "1.2", CVAR_ARCHIVE_ND );
#else
	r_gamma = ri.Cvar_Get( "r_gamma", "1.3", CVAR_ARCHIVE_ND );
#endif
	Cvar_CheckRange( r_gamma, 0.5f, 3.0f, qfalse );
	r_facePlaneCull = ri.Cvar_Get( "r_facePlaneCull", "1", CVAR_ARCHIVE_ND );

	r_railWidth = ri.Cvar_Get( "r_railWidth", "16", CVAR_ARCHIVE_ND );
	r_railCoreWidth = ri.Cvar_Get( "r_railCoreWidth", "1", CVAR_ARCHIVE_ND );
	r_railSegmentLength = ri.Cvar_Get( "r_railSegmentLength", "32", CVAR_ARCHIVE_ND );

	r_primitives = ri.Cvar_Get( "r_primitives", "0", CVAR_ARCHIVE_ND );

	r_ambientScale = ri.Cvar_Get( "r_ambientScale", "0.5", CVAR_CHEAT );
	r_directedScale = ri.Cvar_Get( "r_directedScale", "1", CVAR_CHEAT );

	r_anaglyphMode = ri.Cvar_Get( "r_anaglyphMode", "0", CVAR_ARCHIVE_ND );

	//
	// temporary variables that can change at any time
	//
	r_showImages = ri.Cvar_Get( "r_showImages", "0", CVAR_TEMP );

	r_debugLight = ri.Cvar_Get( "r_debuglight", "0", CVAR_TEMP );
	r_debugSort = ri.Cvar_Get( "r_debugSort", "0", CVAR_CHEAT );
	r_printShaders = ri.Cvar_Get( "r_printShaders", "0", 0 );
	r_saveFontData = ri.Cvar_Get( "r_saveFontData", "0", 0 );

	// Ridah
	// TTimo show_bug.cgi?id=440
	//   with r_cache enabled, non-win32 OSes were leaking 24Mb per R_Init..
	r_cache = ri.Cvar_Get( "r_cache", "1", CVAR_LATCH );  // leaving it as this for backwards compability. but it caches models and shaders also
// (SA) disabling cacheshaders
//	ri.Cvar_Set( "r_cacheShaders", "0");
	// Gordon: enabling again..
	r_cacheShaders = ri.Cvar_Get( "r_cacheShaders", "1", CVAR_LATCH );
//----(SA)	end

	r_cacheModels = ri.Cvar_Get( "r_cacheModels", "1", CVAR_LATCH );
	r_cacheGathering = ri.Cvar_Get( "cl_cacheGathering", "0", 0 );
	r_buildScript = ri.Cvar_Get( "com_buildscript", "0", 0 );
	r_bonesDebug = ri.Cvar_Get( "r_bonesDebug", "0", CVAR_CHEAT );
	// done.

	// Rafael - wolf fog
	r_wolffog = ri.Cvar_Get( "r_wolffog", "1", CVAR_CHEAT ); // JPW NERVE cheat protected per id request
	// done

	r_nocurves = ri.Cvar_Get( "r_nocurves", "0", CVAR_CHEAT );
	r_drawworld = ri.Cvar_Get( "r_drawworld", "1", CVAR_CHEAT );
	r_drawfoliage = ri.Cvar_Get( "r_drawfoliage", "1", CVAR_CHEAT );  // ydnar
	r_lightmap = ri.Cvar_Get( "r_lightmap", "0", CVAR_CHEAT ); // DHM - NERVE :: cheat protect
	r_portalOnly = ri.Cvar_Get( "r_portalOnly", "0", CVAR_CHEAT );

	r_flareSize = ri.Cvar_Get( "r_flareSize", "40", CVAR_CHEAT );
	ri.Cvar_Set( "r_flareFade", "5" ); // to force this when people already have "7" in their config
	r_flareFade = ri.Cvar_Get( "r_flareFade", "5", CVAR_CHEAT );

	r_skipBackEnd = ri.Cvar_Get( "r_skipBackEnd", "0", CVAR_CHEAT );

	r_lodscale = ri.Cvar_Get( "r_lodscale", "5", CVAR_CHEAT );
	r_norefresh = ri.Cvar_Get( "r_norefresh", "0", CVAR_CHEAT );
	r_drawentities = ri.Cvar_Get( "r_drawentities", "1", CVAR_CHEAT );
	r_ignore = ri.Cvar_Get( "r_ignore", "1", CVAR_CHEAT );
	r_nocull = ri.Cvar_Get( "r_nocull", "0", CVAR_CHEAT );
	r_novis = ri.Cvar_Get( "r_novis", "0", CVAR_CHEAT );
	r_showcluster = ri.Cvar_Get( "r_showcluster", "0", CVAR_CHEAT );
	r_speeds = ri.Cvar_Get( "r_speeds", "0", CVAR_CHEAT );
	r_verbose = ri.Cvar_Get( "r_verbose", "0", CVAR_CHEAT );
	r_logFile = ri.Cvar_Get( "r_logFile", "0", CVAR_CHEAT );
	r_debugSurface = ri.Cvar_Get( "r_debugSurface", "0", CVAR_CHEAT );
	r_nobind = ri.Cvar_Get( "r_nobind", "0", CVAR_CHEAT );
	r_showtris = ri.Cvar_Get( "r_showtris", "0", CVAR_CHEAT );
	r_trisColor = ri.Cvar_Get( "r_trisColor", "1.0 1.0 1.0 1.0", CVAR_ARCHIVE );
	r_showsky = ri.Cvar_Get( "r_showsky", "0", CVAR_CHEAT );
	r_shownormals = ri.Cvar_Get( "r_shownormals", "0", CVAR_CHEAT );
	r_normallength = ri.Cvar_Get( "r_normallength", "0.5", CVAR_ARCHIVE );
	r_showmodelbounds = ri.Cvar_Get( "r_showmodelbounds", "0", CVAR_CHEAT );
	r_clear = ri.Cvar_Get( "r_clear", "0", CVAR_CHEAT );
	r_offsetFactor = ri.Cvar_Get( "r_offsetfactor", "-1", CVAR_CHEAT );
	r_offsetUnits = ri.Cvar_Get( "r_offsetunits", "-2", CVAR_CHEAT );
	r_drawBuffer = ri.Cvar_Get( "r_drawBuffer", "GL_BACK", CVAR_CHEAT );
	r_lockpvs = ri.Cvar_Get( "r_lockpvs", "0", CVAR_CHEAT );
	r_noportals = ri.Cvar_Get( "r_noportals", "0", CVAR_CHEAT );
	r_shadows = ri.Cvar_Get( "cg_shadows", "1", 0 );

	r_portalsky = ri.Cvar_Get( "cg_skybox", "1", 0 );

	r_aviMotionJpegQuality = ri.Cvar_Get( "r_aviMotionJpegQuality", "90", CVAR_ARCHIVE_ND );
	r_screenshotJpegQuality = ri.Cvar_Get( "r_screenshotJpegQuality", "90", CVAR_ARCHIVE_ND );
	r_maxpolys = ri.Cvar_Get( "r_maxpolys", va( "%d", MAX_POLYS ), 0 );
	r_maxpolyverts = ri.Cvar_Get( "r_maxpolyverts", va( "%d", MAX_POLYVERTS ), 0 );

	r_highQualityVideo = ri.Cvar_Get( "r_highQualityVideo", "1", CVAR_ARCHIVE );
	
	r_floatfix = ri.Cvar_Get( "r_floatfix", "0", 0 ); // -EC-

	// make sure all the commands added here are also
	// removed in R_Shutdown
	ri.Cmd_AddCommand( "imagelist", R_ImageList_f );
	ri.Cmd_AddCommand( "shaderlist", R_ShaderList_f );
	ri.Cmd_AddCommand( "skinlist", R_SkinList_f );
	ri.Cmd_AddCommand( "modellist", R_Modellist_f );
	ri.Cmd_AddCommand( "modelist", R_ModeList_f );
	ri.Cmd_AddCommand( "screenshot", R_ScreenShot_f );
	ri.Cmd_AddCommand( "screenshotJPEG", R_ScreenShot_f );
	ri.Cmd_AddCommand( "gfxinfo", GfxInfo_f );
	ri.Cmd_AddCommand( "taginfo", R_TagInfo_f );
}

/*
===============
R_Init
===============
*/
void R_Init( void ) {	
	int	err;
	int i;
	byte *ptr;

	ri.Printf( PRINT_ALL, "----- R_Init -----\n" );

	// clear all our internal state
	Com_Memset( &tr, 0, sizeof( tr ) );
	Com_Memset( &backEnd, 0, sizeof( backEnd ) );
	Com_Memset( &tess, 0, sizeof( tess ) );

	//Swap_Init();

	if ( (intptr_t)tess.xyz & 15 ) {
		ri.Printf( PRINT_WARNING, "tess.xyz not 16 byte aligned\n" );
	}
	Com_Memset( tess.constantColor255, 255, sizeof( tess.constantColor255 ) );

	//
	// init function tables
	//
	for ( i = 0; i < FUNCTABLE_SIZE; i++ )
	{
		tr.sinTable[i]		= sin( DEG2RAD( i * 360.0f / ( ( float ) ( FUNCTABLE_SIZE - 1 ) ) ) );
		tr.squareTable[i]	= ( i < FUNCTABLE_SIZE/2 ) ? 1.0f : -1.0f;
		tr.sawToothTable[i] = (float)i / FUNCTABLE_SIZE;
		tr.inverseSawToothTable[i] = 1.0f - tr.sawToothTable[i];

		if ( i < FUNCTABLE_SIZE / 2 )
		{
			if ( i < FUNCTABLE_SIZE / 4 )
			{
				tr.triangleTable[i] = ( float ) i / ( FUNCTABLE_SIZE / 4 );
			}
			else
			{
				tr.triangleTable[i] = 1.0f - tr.triangleTable[i-FUNCTABLE_SIZE / 4];
			}
		}
		else
		{
			tr.triangleTable[i] = -tr.triangleTable[i-FUNCTABLE_SIZE/2];
		}
	}

	// Ridah, init the virtual memory
	R_Hunk_Begin();

	R_InitFogTable();

	R_NoiseInit();

	R_Register();

	R_BloomInit();

	max_polys = r_maxpolys->integer;
	if (max_polys < MAX_POLYS)
		max_polys = MAX_POLYS;

	max_polyverts = r_maxpolyverts->integer;
	if (max_polyverts < MAX_POLYVERTS)
		max_polyverts = MAX_POLYVERTS;
	
	ptr = ri.Hunk_Alloc( sizeof( *backEndData ) + sizeof(srfPoly_t) * max_polys + sizeof(polyVert_t) * max_polyverts, h_low);
	backEndData = (backEndData_t *) ptr;
	//backEndData->polys = (srfPoly_t *) ((char *) ptr + sizeof( *backEndData ));
	//backEndData->polyVerts = (polyVert_t *) ((char *) ptr + sizeof( *backEndData ) + sizeof(srfPoly_t) * max_polys);
	
	R_InitNextFrame();

	InitOpenGL();

	R_InitImages();

	R_InitShaders();

	R_InitSkins();

	R_ModelInit();

	R_InitFreeType();


	err = qglGetError();
	if ( err != GL_NO_ERROR )
		ri.Printf (PRINT_ALL, "glGetError() = 0x%x\n", err);

	ri.Printf( PRINT_ALL, "----- finished R_Init -----\n" );
}

void R_PurgeCache( void ) {
	R_PurgeShaders( 9999999 );
	R_PurgeBackupImages( 9999999 );
	R_PurgeModels( 9999999 );
}

/*
===============
RE_Shutdown
===============
*/
void RE_Shutdown( qboolean destroyWindow ) {	

	ri.Printf( PRINT_ALL, "RE_Shutdown( %i )\n", destroyWindow );

	ri.Cmd_RemoveCommand( "modellist" );
	ri.Cmd_RemoveCommand( "screenshotJPEG" );
	ri.Cmd_RemoveCommand( "screenshot" );
	ri.Cmd_RemoveCommand( "imagelist" );
	ri.Cmd_RemoveCommand( "shaderlist" );
	ri.Cmd_RemoveCommand( "skinlist" );
	ri.Cmd_RemoveCommand( "gfxinfo" );
	ri.Cmd_RemoveCommand( "modelist" );
	ri.Cmd_RemoveCommand( "shaderstate" );
	ri.Cmd_RemoveCommand( "taginfo" );

	// Ridah
	ri.Cmd_RemoveCommand( "cropimages" );
	// done.

	// Ridah, keep a backup of the current images if possible
	// clean out any remaining unused media from the last backup
	R_PurgeCache();

	if ( r_cache->integer ) {
		if ( tr.registered ) {
			if ( destroyWindow ) {
				R_IssuePendingRenderCommands();
				R_DeleteTextures();
			} else {
				// backup the current media

				R_BackupModels();
				R_BackupShaders();
				R_BackupImages();
			}
		}
	} else if ( tr.registered ) {
		R_IssuePendingRenderCommands();
		R_DeleteTextures();
	}

	R_DoneFreeType();

	// shut down platform specific OpenGL stuff
	if ( destroyWindow ) {
		GLimp_Shutdown();

		Com_Memset( &glConfig, 0, sizeof( glConfig ) );
		Com_Memset( &glConfigExt, 0, sizeof( glConfigExt ) );
		Com_Memset( &glState, 0, sizeof( glState ) );

		// Ridah, release the virtual memory
		R_Hunk_End();
		R_FreeImageBuffer();
		ri.Tag_Free();  // wipe all render alloc'd zone memory
	}

	tr.registered = qfalse;
}


/*
=============
RE_EndRegistration

Touch all images to make sure they are resident
=============
*/
void RE_EndRegistration( void ) {
	R_IssuePendingRenderCommands();
	if ( !Sys_LowPhysicalMemory() ) {
//		RB_ShowImages();
	}
}

void R_DebugPolygon( int color, int numPoints, float *points );

/*
@@@@@@@@@@@@@@@@@@@@@
GetRefAPI

@@@@@@@@@@@@@@@@@@@@@
*/
#ifdef USE_RENDERER_DLOPEN
Q_EXPORT refexport_t* QDECL GetRefAPI ( int apiVersion, refimport_t *rimp ) {
#else
refexport_t *GetRefAPI ( int apiVersion, refimport_t *rimp ) {
#endif

	static refexport_t	re;

	ri = *rimp;

	Com_Memset( &re, 0, sizeof( re ) );

	if ( apiVersion != REF_API_VERSION ) {
		ri.Printf(PRINT_ALL, "Mismatched REF_API_VERSION: expected %i, got %i\n", 
			REF_API_VERSION, apiVersion );
		return NULL;
	}

	// the RE_ functions are Renderer Entry points

	re.Shutdown = RE_Shutdown;

	re.BeginRegistration = RE_BeginRegistration;
	re.RegisterModel    = RE_RegisterModel;
	re.RegisterSkin     = RE_RegisterSkin;
//----(SA) added
	re.GetSkinModel         = RE_GetSkinModel;
	re.GetShaderFromModel   = RE_GetShaderFromModel;
//----(SA) end
	re.RegisterShader   = RE_RegisterShader;
	re.RegisterShaderNoMip = RE_RegisterShaderNoMip;
	re.LoadWorld        = RE_LoadWorldMap;
	re.SetWorldVisData  = RE_SetWorldVisData;
	re.EndRegistration  = RE_EndRegistration;

	re.BeginFrame       = RE_BeginFrame;
	re.EndFrame         = RE_EndFrame;

	re.MarkFragments    = R_MarkFragments;
	re.ProjectDecal     = RE_ProjectDecal;
	re.ClearDecals      = RE_ClearDecals;

	re.LerpTag          = R_LerpTag;
	re.ModelBounds      = R_ModelBounds;

	re.ClearScene       = RE_ClearScene;
	re.AddRefEntityToScene = RE_AddRefEntityToScene;
	re.AddPolyToScene   = RE_AddPolyToScene;
	// Ridah
	re.AddPolysToScene  = RE_AddPolysToScene;
	// done.
	re.AddLightToScene  = RE_AddLightToScene;
//----(SA)
	re.AddCoronaToScene = RE_AddCoronaToScene;
	re.SetFog           = R_SetFog;
//----(SA)
	re.RenderScene      = RE_RenderScene;
	re.SaveViewParms    = RE_SaveViewParms;
	re.RestoreViewParms = RE_RestoreViewParms;

	re.SetColor         = RE_SetColor;
	re.DrawStretchPic   = RE_StretchPic;
	re.DrawRotatedPic   = RE_RotatedPic;        // NERVE - SMF
	re.Add2dPolys       = RE_2DPolyies;
	re.DrawStretchPicGradient   = RE_StretchPicGradient;
	re.DrawStretchRaw   = RE_StretchRaw;
	re.UploadCinematic  = RE_UploadCinematic;
	re.RegisterFont     = RE_RegisterFont;
	re.RemapShader      = R_RemapShader;
	re.GetEntityToken   = R_GetEntityToken;

	re.DrawDebugPolygon = R_DebugPolygon;
	re.DrawDebugText    = R_DebugText;

	re.AddPolyBufferToScene =   RE_AddPolyBufferToScene;

	re.SetGlobalFog     = RE_SetGlobalFog;

	re.inPVS = R_inPVS;

	re.purgeCache       = R_PurgeCache;

	//bani
	re.LoadDynamicShader = RE_LoadDynamicShader;
	re.GetTextureId = R_GetTextureId;
	// fretn
	re.RenderToTexture = RE_RenderToTexture;
	//bani
	re.Finish = RE_Finish;

	re.TakeVideoFrame = RE_TakeVideoFrame;

	return &re;
}
