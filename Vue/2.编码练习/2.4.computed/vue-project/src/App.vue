<template>
    <div>
        姓:<input v-model="firstName" placeholder="" placeholder-class="input-placeholder" @input="" />
        名:<input v-model="lastName" placeholder="" placeholder-class="input-placeholder" @input="" />
        全名:<span>{{ fullName }}</span>
        <button @click="changeFullName">全名改为:li-si</button>
    </div>
</template>

<script lang="ts" setup name="Person">
import { computed, ref } from 'vue'

let firstName = ref('zhang')
let lastName = ref('san')

// 计算属性 只读取，不修改
// let fullName = computed(() => {
//     console.log('123')
//     return firstName.value + '-' + lastName.value;
// })

// 计算属性：既读取又修改
let fullName = computed({
    get() {
        return firstName.value + '-' + lastName.value
    },
    set(val) {
        firstName.value = val.split('-')[0]
        lastName.value = val.split('-')[1]
    }
})

function changeFullName() {
    fullName.value = 'li-si'
}

</script>

<style scoped></style>
