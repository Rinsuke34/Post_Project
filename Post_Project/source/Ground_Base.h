#/* �n�`�̃x�[�X�N���X�̐錾 */

#include "Object_Base.h"
#include "AppFrame.h"

// �n�`�x�[�X�N���X
class Ground_Base : public Object_Base
{
	public:
		Ground_Base();					// �R���X�g���N�^
		virtual ~Ground_Base() {};		// �f�X�g���N�^

		/* �֐� */
		virtual void	InitialSetup()	{};	// �����ݒ�
		virtual void	Update()		{};	// �X�V
		virtual void	Draw()			{};	// �`��

		// �R���W�����ڐG����
		virtual bool HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)	{ return false; };	// �J�v�Z��
		virtual bool HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)	{ return false; };	// ����
		virtual bool HitCheck(Struct_Collision::COLLISION_LINE		stLine)		{ return false; };	// ����
};
