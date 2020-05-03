#ifndef ARMOR8VOICE_HPP
#define ARMOR8VOICE_HPP

/*******************************************************************************
 * An ARMor8Voice describes a single voice of the ARMor8tor synthesizer. It
 * statically allocates the required operators, envelope generators, and
 * other requirements for synthesis and provides methods for manipulating
 * them. This file also describes the ARMor8VoiceState, which can be used to
 * store a serializable preset for the synth.
*******************************************************************************/

#include "Operator.hpp"
#include "KeyEventServer.hpp"
#include "ADSREnvelopeGenerator.hpp"
#include "ExponentialResponse.hpp"
#include "PolyBLEPOsc.hpp"
#include "ARMor8Filter.hpp"

// the ARMor8VoiceState struct makes saving voice states for presets easier, since it's easily serializable
struct ARMor8VoiceState
{
	// operator 1
	float frequency1;
	bool  useRatio1;
	OscillatorMode wave1;
	float attack1;
	float attackExpo1;
	float decay1;
	float decayExpo1;
	float sustain1;
	float release1;
	float releaseExpo1;
	bool egAmplitudeMod1;
	bool egFrequencyMod1;
	bool egFilterMod1;
	float op1ModAmount1;
	float op2ModAmount1;
	float op3ModAmount1;
	float op4ModAmount1;
	float amplitude1;
	float filterFreq1;
	float filterRes1;
	float ampVelSens1;
	float filtVelSens1;

	// operator 2
	float frequency2;
	bool  useRatio2;
	OscillatorMode wave2;
	float attack2;
	float attackExpo2;
	float decay2;
	float decayExpo2;
	float sustain2;
	float release2;
	float releaseExpo2;
	bool egAmplitudeMod2;
	bool egFrequencyMod2;
	bool egFilterMod2;
	float op1ModAmount2;
	float op2ModAmount2;
	float op3ModAmount2;
	float op4ModAmount2;
	float amplitude2;
	float filterFreq2;
	float filterRes2;
	float ampVelSens2;
	float filtVelSens2;

	// operator 3
	float frequency3;
	bool  useRatio3;
	OscillatorMode wave3;
	float attack3;
	float attackExpo3;
	float decay3;
	float decayExpo3;
	float sustain3;
	float release3;
	float releaseExpo3;
	bool egAmplitudeMod3;
	bool egFrequencyMod3;
	bool egFilterMod3;
	float op1ModAmount3;
	float op2ModAmount3;
	float op3ModAmount3;
	float op4ModAmount3;
	float amplitude3;
	float filterFreq3;
	float filterRes3;
	float ampVelSens3;
	float filtVelSens3;

	// operator 4
	float frequency4;
	bool  useRatio4;
	OscillatorMode wave4;
	float attack4;
	float attackExpo4;
	float decay4;
	float decayExpo4;
	float sustain4;
	float release4;
	float releaseExpo4;
	bool egAmplitudeMod4;
	bool egFrequencyMod4;
	bool egFilterMod4;
	float op1ModAmount4;
	float op2ModAmount4;
	float op3ModAmount4;
	float op4ModAmount4;
	float amplitude4;
	float filterFreq4;
	float filterRes4;
	float ampVelSens4;
	float filtVelSens4;

	// global
	bool         monophonic;
	unsigned int pitchBendSemitones;
	float        glideTime;
	bool         glideRetrigger;
};

// the ARMor8PresetHeader is intended to be used as a header for the PresetMangager, it tracks the preset version
struct ARMor8PresetHeader
{
	int versionMajor;
	int versionMinor;
	int versionPatch;

	bool presetsFileInitialized;

	bool operator!= (const ARMor8PresetHeader& other)
	{
		if (versionMajor == other.versionMajor && versionMinor == other.versionMinor && versionPatch == other.versionPatch)
		{
			return false;
		}

		return true;
	}
};

class ARMor8Voice
{
	public:
		ARMor8Voice();
		~ARMor8Voice();

		void setOperatorFreq (unsigned int opNum, float freq);
		void setOperatorWave (unsigned int opNum, const OscillatorMode& wave);
		void setOperatorEG (unsigned int opNum, IEnvelopeGenerator* eg);
		void setOperatorEGAttack (unsigned int opNum, float seconds, float expo);
		void setOperatorEGDecay (unsigned int opNum, float seconds, float expo);
		void setOperatorEGSustain (unsigned int opNum, float lvl);
		void setOperatorEGRelease (unsigned int opNum, float seconds, float expo);
		void setOperatorEGModDestination (unsigned int opNum, const EGModDestination& modDest, const bool on);
		void setOperatorModulation (unsigned int sourceOpNum, unsigned int destOpNum, float modulationAmount);
		void setOperatorAmplitude (unsigned int opNum, float amplitude);
		void setOperatorFilterFreq (unsigned int opNum, float frequency);
		void setOperatorFilterRes (unsigned int opNum, float resonance);
		void setOperatorRatio (unsigned int opNum, bool useRatio);
		void setOperatorAmpVelSens (unsigned int opNum, float ampVelSens);
		void setOperatorFiltVelSens (unsigned int opNum, float filtVelSens);
		void setOperatorFrequencyOffset (unsigned int opNum, const float freqOffset);

		void setGlideTime (const float glideTime);
		void setGlideRetrigger (const bool useRetrigger);
		void setUseGlide (const bool useGlide);

		float getOperatorRatioFrequency (unsigned int opNum);
		bool getOperatorUseRatio (unsigned int opNum);

		ARMor8VoiceState getState();
		void setState (const ARMor8VoiceState& state);

		float nextSample();

		void onKeyEvent (const KeyEvent& keyEvent);
		const KeyEvent& getActiveKeyEvent();

		void onPitchEvent (const PitchEvent& pitchEvent);

	private:
		PolyBLEPOsc       	m_Osc1;
		PolyBLEPOsc             m_Osc2;
		PolyBLEPOsc             m_Osc3;
		PolyBLEPOsc             m_Osc4;
		ExponentialResponse    	m_AtkResponse1;
		ExponentialResponse    	m_AtkResponse2;
		ExponentialResponse    	m_AtkResponse3;
		ExponentialResponse    	m_AtkResponse4;
		ExponentialResponse 	m_DecResponse1;
		ExponentialResponse 	m_DecResponse2;
		ExponentialResponse 	m_DecResponse3;
		ExponentialResponse 	m_DecResponse4;
		ExponentialResponse 	m_RelResponse1;
		ExponentialResponse 	m_RelResponse2;
		ExponentialResponse 	m_RelResponse3;
		ExponentialResponse 	m_RelResponse4;
		ADSREnvelopeGenerator 	m_Eg1;
		ADSREnvelopeGenerator 	m_Eg2;
		ADSREnvelopeGenerator 	m_Eg3;
		ADSREnvelopeGenerator 	m_Eg4;
		ARMor8Filter            m_Filt1;
		ARMor8Filter            m_Filt2;
		ARMor8Filter            m_Filt3;
		ARMor8Filter            m_Filt4;
		KeyEventServer 		m_KeyEventServer;
		Operator 		m_Op1;
		Operator 		m_Op2;
		Operator 		m_Op3;
		Operator 		m_Op4;
		Operator* 		m_Operators[4];

		KeyEvent                m_ActiveKeyEvent;
};

#endif // ARMOR8VOICE_HPP
