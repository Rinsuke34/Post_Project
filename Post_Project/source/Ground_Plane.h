/* �n�`(����)�N���X�̐錾 */

#include "Ground_Base.h"

// �n�`(����)�N���X
class Ground_Plane : public Ground_Base
{
	public:
		Ground_Plane();					// �R���X�g���N�^
		virtual ~Ground_Plane() {};		// �f�X�g���N�^

		/* �֐� */
		virtual void	Update();	// �X�V
		virtual void	Draw();		// �`��

		// �R���W�����ڐG����
		bool HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)	override;	// �J�v�Z��
		bool HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)	override;	// ����
		bool HitCheck(Struct_Collision::COLLISION_LINE		stLine)		override;	// ����

	private:
		/* �ϐ� */
		VECTOR		vecNormal;			// �@���x�N�g��
		VECTOR		avecVertex[4];		// ���_���W(4���_)�����v���[0:����,1:�E��,2:�E�O,3,���O]
};
