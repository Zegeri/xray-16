
out gl_PerVertex { vec4 gl_Position; };

layout(location = POSITION)		in float4	v_model_P		; // POSITION;		// (float,float,float,1)
#if defined(SKIN_NONE) || defined(SKIN_0)
layout(location = NORMAL)		in float3	v_model_N		; // NORMAL;		// (nx,ny,nz)
#else
layout(location = NORMAL)		in float4	v_model_N		; // NORMAL;		// (nx,ny,nz,index)
#endif
#if defined(SKIN_3) || defined(SKIN_4)
layout(location = TANGENT)		in float4	v_model_T		; // TANGENT;		// (nx,ny,nz,weight0)
layout(location = BINORMAL)		in float4	v_model_B		; // BINORMAL;		// (nx,ny,nz,weight1)
#else
layout(location = TANGENT)		in float3	v_model_T		; // TANGENT;		// (nx,ny,nz)
layout(location = BINORMAL)		in float3	v_model_B		; // BINORMAL;		// (nx,ny,nz)
#endif
#if defined(SKIN_2) || defined(SKIN_3)
layout(location = TEXCOORD0)	in float4	v_model_tc		; // TEXCOORD0;	// (u,v)
#else
layout(location = TEXCOORD0)	in float2	v_model_tc		; // TEXCOORD0;	// (u,v)
#endif
#ifdef	SKIN_4
layout(location = TEXCOORD1)	in float4	v_model_ind		; // (x=m-index0, y=m-index1, z=m-index2, w=m-index3)
#endif

#if defined(USE_R2_STATIC_SUN) && !defined(USE_LM_HEMI)
layout(location = TEXCOORD0) 	out float4	v2p_flat_tcdh	; // TEXCOORD0;	// Texture coordinates,         w=sun_occlusion
#else
layout(location = TEXCOORD0) 	out float2	v2p_flat_tcdh	; // TEXCOORD0;	// Texture coordinates
#endif
layout(location = TEXCOORD1) 	out float4	v2p_flat_position; // TEXCOORD1;	// position + hemi
layout(location = TEXCOORD2) 	out float3	v2p_flat_N		; // TEXCOORD2;	// Eye-space normal        (for lighting)
#ifdef USE_TDETAIL
layout(location = TEXCOORD3) 	out float2	v2p_flat_tcdbump; // TEXCOORD3;	// d-bump
#endif
#ifdef USE_LM_HEMI
layout(location = TEXCOORD4) 	out float2	v2p_flat_lmh	; // TEXCOORD4;	// lm-hemi
#endif

v2p_flat _main( v_model I );

void main()
{
#ifdef 	SKIN_NONE
	v_model I;
#endif
#ifdef 	SKIN_0
	v_model_skinned_0 I;
#endif
#ifdef	SKIN_1
	v_model_skinned_1 I;
#endif
#ifdef	SKIN_2
	v_model_skinned_2 I;
#endif
#ifdef	SKIN_3
	v_model_skinned_3 I;
#endif
#ifdef	SKIN_4
	v_model_skinned_4 I;
	I.ind = v_model_ind;
#endif

	I.P = v_model_P;
	I.N = v_model_N;
	I.T = v_model_T;
	I.B = v_model_B;
	I.tc = v_model_tc;

	v2p_flat O;
#ifdef 	SKIN_NONE
	O = _main(I);
#endif
#ifdef 	SKIN_0
	O = _main(skinning_0(I));
#endif
#ifdef	SKIN_1
	O = _main(skinning_1(I));
#endif
#ifdef	SKIN_2
	O = _main(skinning_2(I));
#endif
#ifdef	SKIN_3
	O = _main(skinning_3(I));
#endif
#ifdef	SKIN_4
	O = _main(skinning_4(I));
#endif

	v2p_flat_tcdh = O.tcdh;
	v2p_flat_position = O.position;
	v2p_flat_N	= O.N;
#ifdef USE_TDETAIL
	v2p_flat_tcdbump = O.tcdbump;
#endif
#ifdef USE_LM_HEMI
	v2p_flat_lmh = O.lmh;
#endif
	gl_Position = O.hpos;
}
