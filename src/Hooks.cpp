#include "Hooks.h"
#include "Settings.h"
#include "CharacterHandler.h"

namespace Hooks
{
	template <size_t BRANCH_TYPE, uint64_t ID, size_t offset = 0, bool call = false>
	void add_trampoline(Xbyak::CodeGenerator* xbyakCode)
	{
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto funcAddr = funcOffset.address();
		auto size = xbyakCode->getSize();
		auto& trampoline = SKSE::GetTrampoline();
		auto result = trampoline.allocate(size);
		std::memcpy(result, xbyakCode->getCode(), size);
		if constexpr (!call)
			trampoline.write_branch<BRANCH_TYPE>(funcAddr + offset, (std::uintptr_t)result);
		else
			trampoline.write_call<BRANCH_TYPE>(funcAddr + offset, (std::uintptr_t)result);
	}

	template <int ID, int OFFSET>
	void apply_call(std::uintptr_t func)
	{
		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t jump_addr)
			{
				mov(rax, jump_addr);
				jmp(rax);
			}
		} xbyakCode{ func };
		add_trampoline<5, ID, OFFSET, true>(&xbyakCode);
	}

	template <int ID>
	void apply_func(std::uintptr_t func)
	{
		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t jump_addr)
			{
				mov(rax, jump_addr);
				jmp(rax);
			}
		} xbyakCode{ func };
		add_trampoline<6, ID>(&xbyakCode);
	}

	void apply_another_get_chance(std::uintptr_t is_strong)
	{
		const int ID = 49747, BRANCH_TYPE = 5;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto funcAddr = funcOffset.address();

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t is_strong_addr, uintptr_t ret_addr)
			{
				Xbyak::Label still_strong;

				push(rcx);
				push(rdx);
				sub(rsp, 40);
				mov(rax, is_strong_addr);
				call(rax);
				add(rsp, 40);
				pop(rdx);
				pop(rcx);

				test(al, al);
				jnz(still_strong);
				xorps(xmm0, xmm0);
				ret();

				L(still_strong);
				mov(ptr[rsp + 8], rbx);  // recover
				mov(rax, ret_addr);
				jmp(rax);
			}
		} xbyakCode{ is_strong, funcAddr + BRANCH_TYPE };
		add_trampoline<BRANCH_TYPE, ID>(&xbyakCode);
	}

	void apply_get_CombatSpecialAttackChance(std::uintptr_t is_strong)
	{
		const int ID = 49749, BRANCH_TYPE = 5;
		constexpr REL::ID funcOffset(ID);
		auto funcAddr = funcOffset.address();
		constexpr REL::ID subOffset(37586);
		auto subAddr = subOffset.address();

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t is_strong_addr, uintptr_t ret_addr, uintptr_t sub_addr)
			{
				Xbyak::Label still_strong;

				push(rcx);
				push(rdx);
				sub(rsp, 48);
				mov(rax, is_strong_addr);
				call(rax);
				add(rsp, 48);
				pop(rdx);
				pop(rcx);

				test(al, al);
				jnz(still_strong);
				xorps(xmm0, xmm0);
				add(rsp, 0x28);  // recover
				ret();

				L(still_strong);
				mov(rax, ret_addr);
				push(rax);
				mov(rax, sub_addr);
				jmp(rax);
			}
		} xbyakCode{ is_strong, funcAddr + 0x4 + BRANCH_TYPE, subAddr };
		add_trampoline<BRANCH_TYPE, ID, 0x4>(&xbyakCode);
	}

	void apply_get_CombatRangedAttackChance(std::uintptr_t is_strong)
	{
		const int ID = 49772, BRANCH_TYPE = 6;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto funcAddr = funcOffset.address();

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t is_strong_addr, uintptr_t ret_addr)
			{
				Xbyak::Label still_strong;

				push(rcx);
				push(rdx);
				sub(rsp, 40);
				mov(rax, is_strong_addr);
				call(rax);
				add(rsp, 40);
				pop(rdx);
				pop(rcx);

				test(al, al);
				jnz(still_strong);
				xorps(xmm0, xmm0);
				ret();

				L(still_strong);
				push(rbx);       // recover
				sub(rsp, 0x40);  // recover
				mov(rax, ret_addr);
				jmp(rax);
			}
		} xbyakCode{ is_strong, funcAddr + BRANCH_TYPE };
		add_trampoline<BRANCH_TYPE, ID>(&xbyakCode);
	}

	void apply_get_CombatBashChance(std::uintptr_t is_strong)
	{
		const int ID = 49755, BRANCH_TYPE = 5;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto funcAddr = funcOffset.address();

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t is_strong_addr, uintptr_t ret_addr)
			{
				Xbyak::Label still_strong;

				push(rcx);
				push(rdx);
				sub(rsp, 40);
				mov(rax, is_strong_addr);
				call(rax);
				add(rsp, 40);
				pop(rdx);
				pop(rcx);

				test(al, al);
				jnz(still_strong);
				xorps(xmm0, xmm0);
				ret();

				L(still_strong);
				mov(ptr[rsp + 8], rbx);	 // recover
				mov(rax, ret_addr);
				jmp(rax);
			}
		} xbyakCode{ is_strong, funcAddr + BRANCH_TYPE };
		add_trampoline<BRANCH_TYPE, ID>(&xbyakCode);
	}

	void apply_get_CombatBlockChance(std::uintptr_t is_strong)
	{
		const int ID = 49751, BRANCH_TYPE = 6;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto funcAddr = funcOffset.address();

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t is_strong_addr, uintptr_t ret_addr)
			{
				Xbyak::Label still_strong;

				push(rcx);
				push(rdx);
				sub(rsp, 40);
				mov(rax, is_strong_addr);
				call(rax);
				add(rsp, 40);
				pop(rdx);
				pop(rcx);

				test(al, al);
				jnz(still_strong);
				xorps(xmm0, xmm0);
				ret();

				L(still_strong);
				push(rbx);  // recover
				sub(rsp, 0x30);  // recover
				mov(rax, ret_addr);
				jmp(rax);
			}
		} xbyakCode{ is_strong, funcAddr + BRANCH_TYPE };
		add_trampoline<BRANCH_TYPE, ID>(&xbyakCode);
	}

	void apply_get_OffensiveBashChance(std::uintptr_t is_strong)
	{
		const int ID = 49756, BRANCH_TYPE = 5;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto funcAddr = funcOffset.address();

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t is_strong_addr, uintptr_t ret_addr)
			{
				Xbyak::Label still_strong;

				push(rcx);
				push(rdx);
				sub(rsp, 40);
				mov(rax, is_strong_addr);
				call(rax);
				add(rsp, 40);
				pop(rdx);
				pop(rcx);

				test(al, al);
				jnz(still_strong);
				xorps(xmm0, xmm0);
				ret();

				L(still_strong);
				mov(ptr[rsp + 8], rbx);	 // recover
				mov(rax, ret_addr);
				jmp(rax);
			}
		} xbyakCode{ is_strong, funcAddr + BRANCH_TYPE };
		add_trampoline<BRANCH_TYPE, ID>(&xbyakCode);
	}

	void apply_get_CombatBlockAttackChance(std::uintptr_t is_strong)
	{
		const int ID = 49750, BRANCH_TYPE = 5;
		constexpr REL::ID funcOffset(ID);
		auto funcAddr = funcOffset.address();
		constexpr REL::ID subOffset(49711);
		auto subAddr = subOffset.address();

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t is_strong_addr, uintptr_t ret_addr, uintptr_t sub_addr)
			{
				Xbyak::Label still_strong;

				push(rcx);
				push(rdx);
				sub(rsp, 48);
				mov(rax, is_strong_addr);
				call(rax);
				add(rsp, 48);
				pop(rdx);
				pop(rcx);

				test(al, al);
				jnz(still_strong);
				xorps(xmm0, xmm0);
				add(rsp, 0x28);	 // recover
				ret();

				L(still_strong);
				mov(rax, ret_addr);
				push(rax);
				mov(rax, sub_addr);
				jmp(rax);
			}
		} xbyakCode{ is_strong, funcAddr + 0x4 + BRANCH_TYPE, subAddr };
		add_trampoline<BRANCH_TYPE, ID, 0x4>(&xbyakCode);
	}

	void apply_deny_bow_Player()
	{
		// SkyrimSE.exe+74B769(+0x5F9) -- SkyrimSE.exe+74B779(+0x609)
		const int ID = 42928, BRANCH_TYPE = 6;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto retAddr = std::uintptr_t(funcOffset.address() + 0x609);

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t jump_addr, uintptr_t retaddr)
			{
				movaps(xmm3, xmm6);
				mov(rax, jump_addr);
				call(rax);
				mov(rax, retaddr);
				jmp(rax);
			}
		} xbyakCode{ std::uintptr_t(PlayerHandler::deny_bow_Player), retAddr };
		add_trampoline<BRANCH_TYPE, ID, 0x5F9>(&xbyakCode);
	}

	void apply_Actor__jump(std::uintptr_t f)
	{
		// SkyrimSE.exe+7091B4
		const int ID = 41349, BRANCH_TYPE = 5;

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t jump_addr)
			{
				mov(rax, jump_addr);
				jmp(rax);
			}
		} xbyakCode{ f };
		add_trampoline<BRANCH_TYPE, ID, 0x114>(&xbyakCode);
	}

	void apply_PlayerControls__sub_140705530()
	{
		// SkyrimSE.exe+709787
		const int ID = 41361, CALL_TYPE = 6;

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t jump_addr)
			{
				push(rax);
				sub(rsp, 0x20);

				mov(r9, rax);
				mov(rax, jump_addr);
				call(rax);

				add(rsp, 0x20);
				pop(rax);

				mov(ecx, ptr[rax + 0xC4]);
				ret();
			}
		} xbyakCode{ std::uintptr_t(PlayerHandler::PlayerControls__sub_140705530_hooked) };
		add_trampoline<CALL_TYPE, ID, 0xD7, true>(&xbyakCode);

		constexpr REL::ID funcOffset(ID);
		const char data_end[] = "\x0F\x1F\x44\x00\x00";
		REL::safe_write(funcOffset.address() + 0xCB, data_end, 4);  // ????? why not 5
	}

	void apply_deny_player_attack_or_bash()
	{
		const int ID = 38047;

		// SkyrimSE.exe+63D06B
		apply_call<ID, 0xBB>((uintptr_t)CharHandler::deny_player_attack_isstrong);

		constexpr REL::ID funcOffset(ID);
		const char data[] = "\x84\xc0\x75\x38\xeb\x1d";
		REL::safe_write(funcOffset.address() + 0xC0, data, 6);
	}

	void aplly_cost_jump_Player()
	{
		// SkyrimSE.exe+5D2115(+0x195) -- SkyrimSE.exe+5D211C(+0x19C)
		const int ID = 36271, BRANCH_TYPE = 6;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto retAddr = std::uintptr_t(funcOffset.address() + 0x19C);

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t func, uintptr_t retaddr)
			{
				sub(rsp, 0x20);
				movss(ptr[rsp + 0x18], xmm0);
				movss(ptr[rsp + 0x10], xmm6);

				mov(rcx, rdi);
				mov(rax, func);
				call(rax);

				movss(xmm0, ptr[rsp + 0x18]);
				movss(xmm6, ptr[rsp + 0x10]);
				add(rsp, 0x20);

				movaps(xmm7, xmm0);  // restore
				mulss(xmm7, xmm6);

				mov(rax, retaddr);
				jmp(rax);
			}
		} xbyakCode{ std::uintptr_t(PlayerHandler::cost_jump_Player), retAddr };
		add_trampoline<BRANCH_TYPE, ID, 0x195>(&xbyakCode);
	}

	void apply_meleeBash_cost()
	{
		apply_call<37650, 0x16E>((uintptr_t)CharHandler::get_attack_cost);  // SkyrimSE.exe+627A9E

		// SkyrimSE.exe+627A59
		const int ID = 37650;
		constexpr REL::ID funcOffset = REL::ID(ID);
		auto retAddr = std::uintptr_t(funcOffset.address() + 0x132);
		auto retaddr_nulldata = std::uintptr_t(funcOffset.address() + 0x206);

		struct Code : Xbyak::CodeGenerator
		{
			Code(uintptr_t func_nulldata, uintptr_t retaddr, uintptr_t retaddr_nulldata)
			{
				Xbyak::Label nulldata;

				cmp(qword[r14], r12);
				je(nulldata);
				mov(rax, retaddr);
				jmp(rax);

				L(nulldata);
				sub(rsp, 0x20);
				mov(rcx, rbx);
				mov(rax, func_nulldata);
				call(rax);
				add(rsp, 0x20);
				mov(rax, retaddr_nulldata);
				jmp(rax);
			}
		} xbyakCode{ std::uintptr_t(CharHandler::damage_attack_cost_nulldata), retAddr, retaddr_nulldata };
		add_trampoline<6, ID, 0x129>(&xbyakCode);
	}

	void apply_hooks()
	{
		SKSE::AllocTrampoline(1 << 10);

		if (*Settings::meleeNPC) {
			// NPC, deny melee
			apply_another_get_chance(std::uintptr_t(CharHandler::is_strong_attack));
			apply_get_CombatSpecialAttackChance(std::uintptr_t(CharHandler::is_strong_attack));
		}
		if (*Settings::bashNPC) {
			// NPC, deny bash
			apply_get_CombatBashChance(std::uintptr_t(CharHandler::is_strong_bash));
			apply_get_OffensiveBashChance(std::uintptr_t(CharHandler::is_strong_bash));
		}

		if (*Settings::meleePlayer || *Settings::bashPlayer) {
			// deny Player. Melee and (or) bash
			apply_deny_player_attack_or_bash();
		}

		if (*Settings::meleeCostNPC || *Settings::meleeCostPlayer || *Settings::bashCostNPC || *Settings::bashCostPlayer) {
			// cost. NPC and (or) Player. Melee and (or) bash
			apply_meleeBash_cost();
		}
		
		if (*Settings::rangedNPC) {
			// NPC, deny
			apply_get_CombatRangedAttackChance(std::uintptr_t(CharHandler::is_strong_bow_NPC));
		}
		if (*Settings::rangedPlayer) {
			// Player, deny
			apply_deny_bow_Player();
		}
		if (*Settings::rangedCostNPC || *Settings::rangedCostPlayer) {
			// cost, NPC and (or) Player
			apply_call<41778, 0x133>(std::uintptr_t(CharHandler::TESObjectWEAP__Fire_140235240_hooked));  // SkyrimSE.exe+7221E3
		}

		if (*Settings::blockNPC) {
			// NPC, deny
			apply_get_CombatBlockChance(std::uintptr_t(CharHandler::is_strong_block));
			apply_get_CombatBlockAttackChance(std::uintptr_t(CharHandler::is_strong_block));
		}
		if (*Settings::blockPlayer) {
			// Player, deny
			apply_PlayerControls__sub_140705530();
		}
		if (*Settings::blockCostNPC || *Settings::blockCostPlayer) {
			// Both, cost
			apply_call<37633, 0x8D4>(std::uintptr_t(CharHandler::get_block_cost));  // SkyrimSE.exe+626CD4
		}

		if (*Settings::runspeedNPC) {
			// NPC, get slower
			apply_call<49311, 0x2E1>(std::uintptr_t(SpeedHandler::hooked_ActorState__sub_1410C3D40));  // SkyrimSE.exe+83CB51
		}

		if (*Settings::jumpPlayer) {
			// Player, deny
			apply_Actor__jump(std::uintptr_t(PlayerHandler::deny_jump_Player));
		}
		if (*Settings::jumpCost) {
			// Player, cost
			aplly_cost_jump_Player();
		}

		if (*Settings::RegenPlayer || *Settings::RegenNPC) {
			// Both, regen
			apply_call<37510, 0x176>(std::uintptr_t(CharHandler::Custom_regen_140620806));  // SkyrimSE.exe+620806
		}
		if (*Settings::rangedKeepDamage) {
			// Both, keep cost
			apply_call<37510, 0x1B>(std::uintptr_t(CharHandler::ranged_damage_while_keep));  // SkyrimSE.exe+6206AB
		}
	}
}
